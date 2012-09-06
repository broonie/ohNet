using System;
using System.Runtime.InteropServices;
using System.Text;
using OpenHome.Net.Core;
#if IOS
using MonoTouch;
#endif

namespace OpenHome.Net.ControlPoint
{
    /// <summary>
    /// Protocol-independent device
    /// </summary>
    /// <remarks>Instance of this class are reference counted and are automatically deleted
    /// when the reference count falls to zero.
    /// All references to class instances must have been removed before Core.Library.Close() is called.</remarks>
    public class CpDevice
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void CpDeviceCGetUdn(IntPtr aDevice, IntPtr* aUdn, uint* aLen);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpDeviceCAddRef(IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpDeviceCRemoveRef(IntPtr aDevice);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe int CpDeviceCGetAttribute(IntPtr aDevice, IntPtr aKey, char** aValue);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern unsafe void OhNetFree(void* aPtr);

        private IntPtr iHandle;

        /// <summary>
        /// Constructor. Not intended for external use.
        /// </summary>
        /// <remarks>Devices should be constructed via CpDevice or CpDeviceList subclasses.</remarks>
        /// <param name="aHandle">Handle to the underlying native device</param>
        public CpDevice(IntPtr aHandle)
        {
            iHandle = aHandle;
        }

        /// <summary>
        /// Query the unique identifier associated with a device
        /// </summary>
        /// <returns>Device's (universally unique) name</returns>
        public unsafe String Udn()
        {
            IntPtr ptr;
            uint len;
            CpDeviceCGetUdn(iHandle, &ptr, &len);
            return InteropUtils.PtrToStringUtf8(ptr, len);
        }
        
        /// <summary>
        /// Claim a reference to a device.
        /// </summary>
        /// <remarks>Can only be called from code that can guarantee another reference is already held.
        /// Each call to AddRef() must later have exactly one matching call to RemoveRef().</remarks>
        public void AddRef()
        {
            CpDeviceCAddRef(iHandle);
        }
        
        /// <summary>
        /// Remove a reference to a device.
        /// </summary>
        /// <remarks>Removing the final reference causes a device to be deleted.</remarks>
        public void RemoveRef()
        {
            CpDeviceCRemoveRef(iHandle);
        }
        
        /// <summary>
        /// Query the value of one of the device's attributes
        /// </summary>
        /// <param name="aKey">The name of the attribute being queried.  Available attributes
        /// will be listed in a protocol-specific header</param>
        /// <param name="aValue">The value of the attribute</param>
        /// <returns>true if the attribute was available on the device; false otherwise.
        /// aValue will not have been set if false is returned</returns>
        public unsafe bool GetAttribute(string aKey, out string aValue)
        {
            IntPtr key = InteropUtils.StringToHGlobalUtf8(aKey);
            char* value;
            int ret = CpDeviceCGetAttribute(iHandle, key, &value);
            Marshal.FreeHGlobal(key);
            if (ret != 0)
            {
                aValue = InteropUtils.PtrToStringUtf8((IntPtr)value);
                OhNetFree(value);
                return true;
            }
            aValue = null;
            return false;
        }
        
        /// <summary>
        /// Get the handle to the underlying native device
        /// </summary>
        /// <returns>Handle to the underlying native device</returns>
        public IntPtr Handle()
        {
            return iHandle;
        }
    }

    public interface ICpDeviceList : IDisposable
    {
        void Refresh();
    }

    /// <summary>
    /// List of devices available on the current subnet
    /// </summary>
    /// <remarks>Runs callbacks when a device is detected on or removed from a network.
    /// Clients can't iterate the list's contents so must take note of the device in their 'added'
    /// callback and remove the device in their 'removed' callback.
    /// Since CpDevice instances are reference counted, a reference must be claimed inside the
    /// 'added' callback and removed inside the 'removed' callback.
    /// 
    /// This class can't be directly instantiated.  Clients should instead use subclasses which
    /// will define policy on how to detect devices etc.
    /// 
    /// Dispose() must be called before Core.Library.Close().</remarks>
    public class CpDeviceList : ICpDeviceList, IDisposable
    {
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpDeviceListDestroy(IntPtr aListHandle);
#if IOS
        [DllImport("__Internal")]
#else
        [DllImport("ohNet")]
#endif
        static extern void CpDeviceListRefresh(IntPtr aListHandle);

        protected IntPtr iHandle;
        protected GCHandle iGch;
        protected ChangeHandler iAdded;
        protected ChangeHandler iRemoved;
        protected CallbackDevice iFnAdded;
        protected CallbackDevice iFnRemoved;

        protected delegate void CallbackDevice(IntPtr aPtr, IntPtr aHandle);

        public delegate void ChangeHandler(CpDeviceList aList, CpDevice aDevice);

        /// <summary>
        /// Refresh the contents of the list.
        /// </summary>
        /// <remarks>This may be a useful way to quickly update a list after a device has been removed
        /// abruptly from the network (without announcing its removal).
        /// 
        /// The 'added' callback may run any time after this is called to notify new devices.
        /// Any removed devices will be notified by a burst of calls to the 'removed' callback
        /// Core.InitParams::MsearchTimeSecs() seconds after this call is made.
        /// There is no notification that a refresh has completed.  Existing CpDevice instances
        /// can be used as normal throughout the refresh.</remarks>
        public void Refresh()
        {
            CpDeviceListRefresh(iHandle);
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle != IntPtr.Zero)
                {
                    CpDeviceListDestroy(iHandle);
                    iHandle = IntPtr.Zero;
                    iGch.Free();
                }
            }
        }

        protected CpDeviceList()
        {
            iGch = GCHandle.Alloc(this);
            iFnAdded = new CallbackDevice(Added);
            iFnRemoved = new CallbackDevice(Removed);
        }

#if IOS
        [MonoPInvokeCallback (typeof (CallbackDevice))]
#endif
        protected static void Added(IntPtr aPtr, IntPtr aHandle)
        {
            CpDevice device = new CpDevice(aHandle);
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpDeviceList list = (CpDeviceList)gch.Target;
            if (list.iAdded != null) {
                CallListChangedDelegate(list.iAdded, list, device);
            }
        }

#if IOS
        [MonoPInvokeCallback (typeof (CallbackDevice))]
#endif
        protected static void Removed(IntPtr aPtr, IntPtr aHandle)
        {
            CpDevice device = new CpDevice(aHandle);
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            CpDeviceList list = (CpDeviceList)gch.Target;
            if (list.iRemoved != null) {
                CallListChangedDelegate(list.iRemoved, list, device);
            }
        }

        private static void CallListChangedDelegate(ChangeHandler aDelegate, CpDeviceList aList, CpDevice aDevice)
        {
            try
            {
                aDelegate(aList, aDevice);
            }
            catch (ProxyError e)
            {
                Console.WriteLine("WARNING: ProxyError ({0}:{1}) thrown from {2} in device list change delegate", e.Code, (e.Description != null ? e.Description : "<none>"), e.TargetSite.Name);
            }
        }
    }
}
