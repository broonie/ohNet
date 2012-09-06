using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using OpenHome.Net.Core;
using OpenHome.Net.ControlPoint;

namespace OpenHome.Net.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgContentDirectory2 : ICpProxy, IDisposable
    {
        void SyncGetSearchCapabilities(out String aSearchCaps);
        void BeginGetSearchCapabilities(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSearchCapabilities(IntPtr aAsyncHandle, out String aSearchCaps);
        void SyncGetSortCapabilities(out String aSortCaps);
        void BeginGetSortCapabilities(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSortCapabilities(IntPtr aAsyncHandle, out String aSortCaps);
        void SyncGetSortExtensionCapabilities(out String aSortExtensionCaps);
        void BeginGetSortExtensionCapabilities(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSortExtensionCapabilities(IntPtr aAsyncHandle, out String aSortExtensionCaps);
        void SyncGetFeatureList(out String aFeatureList);
        void BeginGetFeatureList(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetFeatureList(IntPtr aAsyncHandle, out String aFeatureList);
        void SyncGetSystemUpdateID(out uint aId);
        void BeginGetSystemUpdateID(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetSystemUpdateID(IntPtr aAsyncHandle, out uint aId);
        void SyncBrowse(String aObjectID, String aBrowseFlag, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void BeginBrowse(String aObjectID, String aBrowseFlag, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CpProxy.CallbackAsyncComplete aCallback);
        void EndBrowse(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void SyncSearch(String aContainerID, String aSearchCriteria, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void BeginSearch(String aContainerID, String aSearchCriteria, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CpProxy.CallbackAsyncComplete aCallback);
        void EndSearch(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID);
        void SyncCreateObject(String aContainerID, String aElements, out String aObjectID, out String aResult);
        void BeginCreateObject(String aContainerID, String aElements, CpProxy.CallbackAsyncComplete aCallback);
        void EndCreateObject(IntPtr aAsyncHandle, out String aObjectID, out String aResult);
        void SyncDestroyObject(String aObjectID);
        void BeginDestroyObject(String aObjectID, CpProxy.CallbackAsyncComplete aCallback);
        void EndDestroyObject(IntPtr aAsyncHandle);
        void SyncUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue);
        void BeginUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue, CpProxy.CallbackAsyncComplete aCallback);
        void EndUpdateObject(IntPtr aAsyncHandle);
        void SyncMoveObject(String aObjectID, String aNewParentID, out String aNewObjectID);
        void BeginMoveObject(String aObjectID, String aNewParentID, CpProxy.CallbackAsyncComplete aCallback);
        void EndMoveObject(IntPtr aAsyncHandle, out String aNewObjectID);
        void SyncImportResource(String aSourceURI, String aDestinationURI, out uint aTransferID);
        void BeginImportResource(String aSourceURI, String aDestinationURI, CpProxy.CallbackAsyncComplete aCallback);
        void EndImportResource(IntPtr aAsyncHandle, out uint aTransferID);
        void SyncExportResource(String aSourceURI, String aDestinationURI, out uint aTransferID);
        void BeginExportResource(String aSourceURI, String aDestinationURI, CpProxy.CallbackAsyncComplete aCallback);
        void EndExportResource(IntPtr aAsyncHandle, out uint aTransferID);
        void SyncDeleteResource(String aResourceURI);
        void BeginDeleteResource(String aResourceURI, CpProxy.CallbackAsyncComplete aCallback);
        void EndDeleteResource(IntPtr aAsyncHandle);
        void SyncStopTransferResource(uint aTransferID);
        void BeginStopTransferResource(uint aTransferID, CpProxy.CallbackAsyncComplete aCallback);
        void EndStopTransferResource(IntPtr aAsyncHandle);
        void SyncGetTransferProgress(uint aTransferID, out String aTransferStatus, out String aTransferLength, out String aTransferTotal);
        void BeginGetTransferProgress(uint aTransferID, CpProxy.CallbackAsyncComplete aCallback);
        void EndGetTransferProgress(IntPtr aAsyncHandle, out String aTransferStatus, out String aTransferLength, out String aTransferTotal);
        void SyncCreateReference(String aContainerID, String aObjectID, out String aNewID);
        void BeginCreateReference(String aContainerID, String aObjectID, CpProxy.CallbackAsyncComplete aCallback);
        void EndCreateReference(IntPtr aAsyncHandle, out String aNewID);
        void SetPropertySystemUpdateIDChanged(System.Action aSystemUpdateIDChanged);
        uint PropertySystemUpdateID();
        void SetPropertyContainerUpdateIDsChanged(System.Action aContainerUpdateIDsChanged);
        String PropertyContainerUpdateIDs();
        void SetPropertyTransferIDsChanged(System.Action aTransferIDsChanged);
        String PropertyTransferIDs();
    }

    internal class SyncGetSearchCapabilitiesUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iSearchCaps;

        public SyncGetSearchCapabilitiesUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String SearchCaps()
        {
            return iSearchCaps;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSearchCapabilities(aAsyncHandle, out iSearchCaps);
        }
    };

    internal class SyncGetSortCapabilitiesUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iSortCaps;

        public SyncGetSortCapabilitiesUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String SortCaps()
        {
            return iSortCaps;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSortCapabilities(aAsyncHandle, out iSortCaps);
        }
    };

    internal class SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iSortExtensionCaps;

        public SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String SortExtensionCaps()
        {
            return iSortExtensionCaps;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSortExtensionCapabilities(aAsyncHandle, out iSortExtensionCaps);
        }
    };

    internal class SyncGetFeatureListUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iFeatureList;

        public SyncGetFeatureListUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String FeatureList()
        {
            return iFeatureList;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetFeatureList(aAsyncHandle, out iFeatureList);
        }
    };

    internal class SyncGetSystemUpdateIDUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private uint iId;

        public SyncGetSystemUpdateIDUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public uint Id()
        {
            return iId;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetSystemUpdateID(aAsyncHandle, out iId);
        }
    };

    internal class SyncBrowseUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iResult;
        private uint iNumberReturned;
        private uint iTotalMatches;
        private uint iUpdateID;

        public SyncBrowseUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint NumberReturned()
        {
            return iNumberReturned;
        }
        public uint TotalMatches()
        {
            return iTotalMatches;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndBrowse(aAsyncHandle, out iResult, out iNumberReturned, out iTotalMatches, out iUpdateID);
        }
    };

    internal class SyncSearchUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iResult;
        private uint iNumberReturned;
        private uint iTotalMatches;
        private uint iUpdateID;

        public SyncSearchUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String Result()
        {
            return iResult;
        }
        public uint NumberReturned()
        {
            return iNumberReturned;
        }
        public uint TotalMatches()
        {
            return iTotalMatches;
        }
        public uint UpdateID()
        {
            return iUpdateID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSearch(aAsyncHandle, out iResult, out iNumberReturned, out iTotalMatches, out iUpdateID);
        }
    };

    internal class SyncCreateObjectUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iObjectID;
        private String iResult;

        public SyncCreateObjectUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String ObjectID()
        {
            return iObjectID;
        }
        public String Result()
        {
            return iResult;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCreateObject(aAsyncHandle, out iObjectID, out iResult);
        }
    };

    internal class SyncDestroyObjectUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;

        public SyncDestroyObjectUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDestroyObject(aAsyncHandle);
        }
    };

    internal class SyncUpdateObjectUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;

        public SyncUpdateObjectUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndUpdateObject(aAsyncHandle);
        }
    };

    internal class SyncMoveObjectUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iNewObjectID;

        public SyncMoveObjectUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String NewObjectID()
        {
            return iNewObjectID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndMoveObject(aAsyncHandle, out iNewObjectID);
        }
    };

    internal class SyncImportResourceUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private uint iTransferID;

        public SyncImportResourceUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public uint TransferID()
        {
            return iTransferID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndImportResource(aAsyncHandle, out iTransferID);
        }
    };

    internal class SyncExportResourceUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private uint iTransferID;

        public SyncExportResourceUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public uint TransferID()
        {
            return iTransferID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndExportResource(aAsyncHandle, out iTransferID);
        }
    };

    internal class SyncDeleteResourceUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;

        public SyncDeleteResourceUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndDeleteResource(aAsyncHandle);
        }
    };

    internal class SyncStopTransferResourceUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;

        public SyncStopTransferResourceUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStopTransferResource(aAsyncHandle);
        }
    };

    internal class SyncGetTransferProgressUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iTransferStatus;
        private String iTransferLength;
        private String iTransferTotal;

        public SyncGetTransferProgressUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String TransferStatus()
        {
            return iTransferStatus;
        }
        public String TransferLength()
        {
            return iTransferLength;
        }
        public String TransferTotal()
        {
            return iTransferTotal;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetTransferProgress(aAsyncHandle, out iTransferStatus, out iTransferLength, out iTransferTotal);
        }
    };

    internal class SyncCreateReferenceUpnpOrgContentDirectory2 : SyncProxyAction
    {
        private CpProxyUpnpOrgContentDirectory2 iService;
        private String iNewID;

        public SyncCreateReferenceUpnpOrgContentDirectory2(CpProxyUpnpOrgContentDirectory2 aProxy)
        {
            iService = aProxy;
        }
        public String NewID()
        {
            return iNewID;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndCreateReference(aAsyncHandle, out iNewID);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:ContentDirectory:2 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgContentDirectory2 : CpProxy, IDisposable, ICpProxyUpnpOrgContentDirectory2
    {
        private OpenHome.Net.Core.Action iActionGetSearchCapabilities;
        private OpenHome.Net.Core.Action iActionGetSortCapabilities;
        private OpenHome.Net.Core.Action iActionGetSortExtensionCapabilities;
        private OpenHome.Net.Core.Action iActionGetFeatureList;
        private OpenHome.Net.Core.Action iActionGetSystemUpdateID;
        private OpenHome.Net.Core.Action iActionBrowse;
        private OpenHome.Net.Core.Action iActionSearch;
        private OpenHome.Net.Core.Action iActionCreateObject;
        private OpenHome.Net.Core.Action iActionDestroyObject;
        private OpenHome.Net.Core.Action iActionUpdateObject;
        private OpenHome.Net.Core.Action iActionMoveObject;
        private OpenHome.Net.Core.Action iActionImportResource;
        private OpenHome.Net.Core.Action iActionExportResource;
        private OpenHome.Net.Core.Action iActionDeleteResource;
        private OpenHome.Net.Core.Action iActionStopTransferResource;
        private OpenHome.Net.Core.Action iActionGetTransferProgress;
        private OpenHome.Net.Core.Action iActionCreateReference;
        private PropertyUint iSystemUpdateID;
        private PropertyString iContainerUpdateIDs;
        private PropertyString iTransferIDs;
        private System.Action iSystemUpdateIDChanged;
        private System.Action iContainerUpdateIDsChanged;
        private System.Action iTransferIDsChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgContentDirectory2(CpDevice aDevice)
            : base("schemas-upnp-org", "ContentDirectory", 2, aDevice)
        {
            OpenHome.Net.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionGetSearchCapabilities = new OpenHome.Net.Core.Action("GetSearchCapabilities");
            param = new ParameterString("SearchCaps", allowedValues);
            iActionGetSearchCapabilities.AddOutputParameter(param);

            iActionGetSortCapabilities = new OpenHome.Net.Core.Action("GetSortCapabilities");
            param = new ParameterString("SortCaps", allowedValues);
            iActionGetSortCapabilities.AddOutputParameter(param);

            iActionGetSortExtensionCapabilities = new OpenHome.Net.Core.Action("GetSortExtensionCapabilities");
            param = new ParameterString("SortExtensionCaps", allowedValues);
            iActionGetSortExtensionCapabilities.AddOutputParameter(param);

            iActionGetFeatureList = new OpenHome.Net.Core.Action("GetFeatureList");
            param = new ParameterString("FeatureList", allowedValues);
            iActionGetFeatureList.AddOutputParameter(param);

            iActionGetSystemUpdateID = new OpenHome.Net.Core.Action("GetSystemUpdateID");
            param = new ParameterUint("Id");
            iActionGetSystemUpdateID.AddOutputParameter(param);

            iActionBrowse = new OpenHome.Net.Core.Action("Browse");
            param = new ParameterString("ObjectID", allowedValues);
            iActionBrowse.AddInputParameter(param);
            allowedValues.Add("BrowseMetadata");
            allowedValues.Add("BrowseDirectChildren");
            param = new ParameterString("BrowseFlag", allowedValues);
            iActionBrowse.AddInputParameter(param);
            allowedValues.Clear();
            param = new ParameterString("Filter", allowedValues);
            iActionBrowse.AddInputParameter(param);
            param = new ParameterUint("StartingIndex");
            iActionBrowse.AddInputParameter(param);
            param = new ParameterUint("RequestedCount");
            iActionBrowse.AddInputParameter(param);
            param = new ParameterString("SortCriteria", allowedValues);
            iActionBrowse.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionBrowse.AddOutputParameter(param);
            param = new ParameterUint("NumberReturned");
            iActionBrowse.AddOutputParameter(param);
            param = new ParameterUint("TotalMatches");
            iActionBrowse.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionBrowse.AddOutputParameter(param);

            iActionSearch = new OpenHome.Net.Core.Action("Search");
            param = new ParameterString("ContainerID", allowedValues);
            iActionSearch.AddInputParameter(param);
            param = new ParameterString("SearchCriteria", allowedValues);
            iActionSearch.AddInputParameter(param);
            param = new ParameterString("Filter", allowedValues);
            iActionSearch.AddInputParameter(param);
            param = new ParameterUint("StartingIndex");
            iActionSearch.AddInputParameter(param);
            param = new ParameterUint("RequestedCount");
            iActionSearch.AddInputParameter(param);
            param = new ParameterString("SortCriteria", allowedValues);
            iActionSearch.AddInputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionSearch.AddOutputParameter(param);
            param = new ParameterUint("NumberReturned");
            iActionSearch.AddOutputParameter(param);
            param = new ParameterUint("TotalMatches");
            iActionSearch.AddOutputParameter(param);
            param = new ParameterUint("UpdateID");
            iActionSearch.AddOutputParameter(param);

            iActionCreateObject = new OpenHome.Net.Core.Action("CreateObject");
            param = new ParameterString("ContainerID", allowedValues);
            iActionCreateObject.AddInputParameter(param);
            param = new ParameterString("Elements", allowedValues);
            iActionCreateObject.AddInputParameter(param);
            param = new ParameterString("ObjectID", allowedValues);
            iActionCreateObject.AddOutputParameter(param);
            param = new ParameterString("Result", allowedValues);
            iActionCreateObject.AddOutputParameter(param);

            iActionDestroyObject = new OpenHome.Net.Core.Action("DestroyObject");
            param = new ParameterString("ObjectID", allowedValues);
            iActionDestroyObject.AddInputParameter(param);

            iActionUpdateObject = new OpenHome.Net.Core.Action("UpdateObject");
            param = new ParameterString("ObjectID", allowedValues);
            iActionUpdateObject.AddInputParameter(param);
            param = new ParameterString("CurrentTagValue", allowedValues);
            iActionUpdateObject.AddInputParameter(param);
            param = new ParameterString("NewTagValue", allowedValues);
            iActionUpdateObject.AddInputParameter(param);

            iActionMoveObject = new OpenHome.Net.Core.Action("MoveObject");
            param = new ParameterString("ObjectID", allowedValues);
            iActionMoveObject.AddInputParameter(param);
            param = new ParameterString("NewParentID", allowedValues);
            iActionMoveObject.AddInputParameter(param);
            param = new ParameterString("NewObjectID", allowedValues);
            iActionMoveObject.AddOutputParameter(param);

            iActionImportResource = new OpenHome.Net.Core.Action("ImportResource");
            param = new ParameterString("SourceURI", allowedValues);
            iActionImportResource.AddInputParameter(param);
            param = new ParameterString("DestinationURI", allowedValues);
            iActionImportResource.AddInputParameter(param);
            param = new ParameterUint("TransferID");
            iActionImportResource.AddOutputParameter(param);

            iActionExportResource = new OpenHome.Net.Core.Action("ExportResource");
            param = new ParameterString("SourceURI", allowedValues);
            iActionExportResource.AddInputParameter(param);
            param = new ParameterString("DestinationURI", allowedValues);
            iActionExportResource.AddInputParameter(param);
            param = new ParameterUint("TransferID");
            iActionExportResource.AddOutputParameter(param);

            iActionDeleteResource = new OpenHome.Net.Core.Action("DeleteResource");
            param = new ParameterString("ResourceURI", allowedValues);
            iActionDeleteResource.AddInputParameter(param);

            iActionStopTransferResource = new OpenHome.Net.Core.Action("StopTransferResource");
            param = new ParameterUint("TransferID");
            iActionStopTransferResource.AddInputParameter(param);

            iActionGetTransferProgress = new OpenHome.Net.Core.Action("GetTransferProgress");
            param = new ParameterUint("TransferID");
            iActionGetTransferProgress.AddInputParameter(param);
            allowedValues.Add("COMPLETED");
            allowedValues.Add("ERROR");
            allowedValues.Add("IN_PROGRESS");
            allowedValues.Add("STOPPED");
            param = new ParameterString("TransferStatus", allowedValues);
            iActionGetTransferProgress.AddOutputParameter(param);
            allowedValues.Clear();
            param = new ParameterString("TransferLength", allowedValues);
            iActionGetTransferProgress.AddOutputParameter(param);
            param = new ParameterString("TransferTotal", allowedValues);
            iActionGetTransferProgress.AddOutputParameter(param);

            iActionCreateReference = new OpenHome.Net.Core.Action("CreateReference");
            param = new ParameterString("ContainerID", allowedValues);
            iActionCreateReference.AddInputParameter(param);
            param = new ParameterString("ObjectID", allowedValues);
            iActionCreateReference.AddInputParameter(param);
            param = new ParameterString("NewID", allowedValues);
            iActionCreateReference.AddOutputParameter(param);

            iSystemUpdateID = new PropertyUint("SystemUpdateID", SystemUpdateIDPropertyChanged);
            AddProperty(iSystemUpdateID);
            iContainerUpdateIDs = new PropertyString("ContainerUpdateIDs", ContainerUpdateIDsPropertyChanged);
            AddProperty(iContainerUpdateIDs);
            iTransferIDs = new PropertyString("TransferIDs", TransferIDsPropertyChanged);
            AddProperty(iTransferIDs);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSearchCaps"></param>
        public void SyncGetSearchCapabilities(out String aSearchCaps)
        {
            SyncGetSearchCapabilitiesUpnpOrgContentDirectory2 sync = new SyncGetSearchCapabilitiesUpnpOrgContentDirectory2(this);
            BeginGetSearchCapabilities(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSearchCaps = sync.SearchCaps();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSearchCapabilities().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSearchCapabilities(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSearchCapabilities, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetSearchCapabilities.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSearchCaps"></param>
        public void EndGetSearchCapabilities(IntPtr aAsyncHandle, out String aSearchCaps)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSearchCaps = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSortCaps"></param>
        public void SyncGetSortCapabilities(out String aSortCaps)
        {
            SyncGetSortCapabilitiesUpnpOrgContentDirectory2 sync = new SyncGetSortCapabilitiesUpnpOrgContentDirectory2(this);
            BeginGetSortCapabilities(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSortCaps = sync.SortCaps();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSortCapabilities().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSortCapabilities(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSortCapabilities, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetSortCapabilities.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSortCaps"></param>
        public void EndGetSortCapabilities(IntPtr aAsyncHandle, out String aSortCaps)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSortCaps = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSortExtensionCaps"></param>
        public void SyncGetSortExtensionCapabilities(out String aSortExtensionCaps)
        {
            SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2 sync = new SyncGetSortExtensionCapabilitiesUpnpOrgContentDirectory2(this);
            BeginGetSortExtensionCapabilities(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aSortExtensionCaps = sync.SortExtensionCaps();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSortExtensionCapabilities().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSortExtensionCapabilities(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSortExtensionCapabilities, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetSortExtensionCapabilities.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aSortExtensionCaps"></param>
        public void EndGetSortExtensionCapabilities(IntPtr aAsyncHandle, out String aSortExtensionCaps)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aSortExtensionCaps = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aFeatureList"></param>
        public void SyncGetFeatureList(out String aFeatureList)
        {
            SyncGetFeatureListUpnpOrgContentDirectory2 sync = new SyncGetFeatureListUpnpOrgContentDirectory2(this);
            BeginGetFeatureList(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aFeatureList = sync.FeatureList();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetFeatureList().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetFeatureList(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetFeatureList, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetFeatureList.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aFeatureList"></param>
        public void EndGetFeatureList(IntPtr aAsyncHandle, out String aFeatureList)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aFeatureList = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aId"></param>
        public void SyncGetSystemUpdateID(out uint aId)
        {
            SyncGetSystemUpdateIDUpnpOrgContentDirectory2 sync = new SyncGetSystemUpdateIDUpnpOrgContentDirectory2(this);
            BeginGetSystemUpdateID(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aId = sync.Id();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetSystemUpdateID().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetSystemUpdateID(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetSystemUpdateID, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetSystemUpdateID.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aId"></param>
        public void EndGetSystemUpdateID(IntPtr aAsyncHandle, out uint aId)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aId = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aBrowseFlag"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void SyncBrowse(String aObjectID, String aBrowseFlag, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            SyncBrowseUpnpOrgContentDirectory2 sync = new SyncBrowseUpnpOrgContentDirectory2(this);
            BeginBrowse(aObjectID, aBrowseFlag, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aNumberReturned = sync.NumberReturned();
            aTotalMatches = sync.TotalMatches();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndBrowse().</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aBrowseFlag"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginBrowse(String aObjectID, String aBrowseFlag, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionBrowse, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowse.InputParameter(inIndex++), aObjectID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowse.InputParameter(inIndex++), aBrowseFlag));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowse.InputParameter(inIndex++), aFilter));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowse.InputParameter(inIndex++), aStartingIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionBrowse.InputParameter(inIndex++), aRequestedCount));
            invocation.AddInput(new ArgumentString((ParameterString)iActionBrowse.InputParameter(inIndex++), aSortCriteria));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionBrowse.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowse.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowse.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionBrowse.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void EndBrowse(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aNumberReturned = Invocation.OutputUint(aAsyncHandle, index++);
            aTotalMatches = Invocation.OutputUint(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aSearchCriteria"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void SyncSearch(String aContainerID, String aSearchCriteria, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
            SyncSearchUpnpOrgContentDirectory2 sync = new SyncSearchUpnpOrgContentDirectory2(this);
            BeginSearch(aContainerID, aSearchCriteria, aFilter, aStartingIndex, aRequestedCount, aSortCriteria, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aResult = sync.Result();
            aNumberReturned = sync.NumberReturned();
            aTotalMatches = sync.TotalMatches();
            aUpdateID = sync.UpdateID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSearch().</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aSearchCriteria"></param>
        /// <param name="aFilter"></param>
        /// <param name="aStartingIndex"></param>
        /// <param name="aRequestedCount"></param>
        /// <param name="aSortCriteria"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSearch(String aContainerID, String aSearchCriteria, String aFilter, uint aStartingIndex, uint aRequestedCount, String aSortCriteria, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSearch, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSearch.InputParameter(inIndex++), aContainerID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSearch.InputParameter(inIndex++), aSearchCriteria));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSearch.InputParameter(inIndex++), aFilter));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSearch.InputParameter(inIndex++), aStartingIndex));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSearch.InputParameter(inIndex++), aRequestedCount));
            invocation.AddInput(new ArgumentString((ParameterString)iActionSearch.InputParameter(inIndex++), aSortCriteria));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionSearch.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSearch.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSearch.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionSearch.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aResult"></param>
        /// <param name="aNumberReturned"></param>
        /// <param name="aTotalMatches"></param>
        /// <param name="aUpdateID"></param>
        public void EndSearch(IntPtr aAsyncHandle, out String aResult, out uint aNumberReturned, out uint aTotalMatches, out uint aUpdateID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aResult = Invocation.OutputString(aAsyncHandle, index++);
            aNumberReturned = Invocation.OutputUint(aAsyncHandle, index++);
            aTotalMatches = Invocation.OutputUint(aAsyncHandle, index++);
            aUpdateID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aElements"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aResult"></param>
        public void SyncCreateObject(String aContainerID, String aElements, out String aObjectID, out String aResult)
        {
            SyncCreateObjectUpnpOrgContentDirectory2 sync = new SyncCreateObjectUpnpOrgContentDirectory2(this);
            BeginCreateObject(aContainerID, aElements, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aObjectID = sync.ObjectID();
            aResult = sync.Result();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCreateObject().</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aElements"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCreateObject(String aContainerID, String aElements, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCreateObject, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateObject.InputParameter(inIndex++), aContainerID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateObject.InputParameter(inIndex++), aElements));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCreateObject.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCreateObject.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aObjectID"></param>
        /// <param name="aResult"></param>
        public void EndCreateObject(IntPtr aAsyncHandle, out String aObjectID, out String aResult)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aObjectID = Invocation.OutputString(aAsyncHandle, index++);
            aResult = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aObjectID"></param>
        public void SyncDestroyObject(String aObjectID)
        {
            SyncDestroyObjectUpnpOrgContentDirectory2 sync = new SyncDestroyObjectUpnpOrgContentDirectory2(this);
            BeginDestroyObject(aObjectID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDestroyObject().</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDestroyObject(String aObjectID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDestroyObject, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDestroyObject.InputParameter(inIndex++), aObjectID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDestroyObject(IntPtr aAsyncHandle)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aCurrentTagValue"></param>
        /// <param name="aNewTagValue"></param>
        public void SyncUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue)
        {
            SyncUpdateObjectUpnpOrgContentDirectory2 sync = new SyncUpdateObjectUpnpOrgContentDirectory2(this);
            BeginUpdateObject(aObjectID, aCurrentTagValue, aNewTagValue, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndUpdateObject().</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aCurrentTagValue"></param>
        /// <param name="aNewTagValue"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginUpdateObject(String aObjectID, String aCurrentTagValue, String aNewTagValue, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionUpdateObject, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionUpdateObject.InputParameter(inIndex++), aObjectID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionUpdateObject.InputParameter(inIndex++), aCurrentTagValue));
            invocation.AddInput(new ArgumentString((ParameterString)iActionUpdateObject.InputParameter(inIndex++), aNewTagValue));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndUpdateObject(IntPtr aAsyncHandle)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aNewParentID"></param>
        /// <param name="aNewObjectID"></param>
        public void SyncMoveObject(String aObjectID, String aNewParentID, out String aNewObjectID)
        {
            SyncMoveObjectUpnpOrgContentDirectory2 sync = new SyncMoveObjectUpnpOrgContentDirectory2(this);
            BeginMoveObject(aObjectID, aNewParentID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aNewObjectID = sync.NewObjectID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndMoveObject().</remarks>
        /// <param name="aObjectID"></param>
        /// <param name="aNewParentID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginMoveObject(String aObjectID, String aNewParentID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionMoveObject, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionMoveObject.InputParameter(inIndex++), aObjectID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionMoveObject.InputParameter(inIndex++), aNewParentID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionMoveObject.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aNewObjectID"></param>
        public void EndMoveObject(IntPtr aAsyncHandle, out String aNewObjectID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aNewObjectID = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        public void SyncImportResource(String aSourceURI, String aDestinationURI, out uint aTransferID)
        {
            SyncImportResourceUpnpOrgContentDirectory2 sync = new SyncImportResourceUpnpOrgContentDirectory2(this);
            BeginImportResource(aSourceURI, aDestinationURI, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTransferID = sync.TransferID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndImportResource().</remarks>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginImportResource(String aSourceURI, String aDestinationURI, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionImportResource, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionImportResource.InputParameter(inIndex++), aSourceURI));
            invocation.AddInput(new ArgumentString((ParameterString)iActionImportResource.InputParameter(inIndex++), aDestinationURI));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionImportResource.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTransferID"></param>
        public void EndImportResource(IntPtr aAsyncHandle, out uint aTransferID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aTransferID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aTransferID"></param>
        public void SyncExportResource(String aSourceURI, String aDestinationURI, out uint aTransferID)
        {
            SyncExportResourceUpnpOrgContentDirectory2 sync = new SyncExportResourceUpnpOrgContentDirectory2(this);
            BeginExportResource(aSourceURI, aDestinationURI, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTransferID = sync.TransferID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndExportResource().</remarks>
        /// <param name="aSourceURI"></param>
        /// <param name="aDestinationURI"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginExportResource(String aSourceURI, String aDestinationURI, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionExportResource, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionExportResource.InputParameter(inIndex++), aSourceURI));
            invocation.AddInput(new ArgumentString((ParameterString)iActionExportResource.InputParameter(inIndex++), aDestinationURI));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionExportResource.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTransferID"></param>
        public void EndExportResource(IntPtr aAsyncHandle, out uint aTransferID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aTransferID = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aResourceURI"></param>
        public void SyncDeleteResource(String aResourceURI)
        {
            SyncDeleteResourceUpnpOrgContentDirectory2 sync = new SyncDeleteResourceUpnpOrgContentDirectory2(this);
            BeginDeleteResource(aResourceURI, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndDeleteResource().</remarks>
        /// <param name="aResourceURI"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginDeleteResource(String aResourceURI, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionDeleteResource, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionDeleteResource.InputParameter(inIndex++), aResourceURI));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndDeleteResource(IntPtr aAsyncHandle)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aTransferID"></param>
        public void SyncStopTransferResource(uint aTransferID)
        {
            SyncStopTransferResourceUpnpOrgContentDirectory2 sync = new SyncStopTransferResourceUpnpOrgContentDirectory2(this);
            BeginStopTransferResource(aTransferID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStopTransferResource().</remarks>
        /// <param name="aTransferID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStopTransferResource(uint aTransferID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStopTransferResource, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionStopTransferResource.InputParameter(inIndex++), aTransferID));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStopTransferResource(IntPtr aAsyncHandle)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aTransferID"></param>
        /// <param name="aTransferStatus"></param>
        /// <param name="aTransferLength"></param>
        /// <param name="aTransferTotal"></param>
        public void SyncGetTransferProgress(uint aTransferID, out String aTransferStatus, out String aTransferLength, out String aTransferTotal)
        {
            SyncGetTransferProgressUpnpOrgContentDirectory2 sync = new SyncGetTransferProgressUpnpOrgContentDirectory2(this);
            BeginGetTransferProgress(aTransferID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aTransferStatus = sync.TransferStatus();
            aTransferLength = sync.TransferLength();
            aTransferTotal = sync.TransferTotal();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetTransferProgress().</remarks>
        /// <param name="aTransferID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetTransferProgress(uint aTransferID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetTransferProgress, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionGetTransferProgress.InputParameter(inIndex++), aTransferID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetTransferProgress.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aTransferStatus"></param>
        /// <param name="aTransferLength"></param>
        /// <param name="aTransferTotal"></param>
        public void EndGetTransferProgress(IntPtr aAsyncHandle, out String aTransferStatus, out String aTransferLength, out String aTransferTotal)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aTransferStatus = Invocation.OutputString(aAsyncHandle, index++);
            aTransferLength = Invocation.OutputString(aAsyncHandle, index++);
            aTransferTotal = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aNewID"></param>
        public void SyncCreateReference(String aContainerID, String aObjectID, out String aNewID)
        {
            SyncCreateReferenceUpnpOrgContentDirectory2 sync = new SyncCreateReferenceUpnpOrgContentDirectory2(this);
            BeginCreateReference(aContainerID, aObjectID, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aNewID = sync.NewID();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndCreateReference().</remarks>
        /// <param name="aContainerID"></param>
        /// <param name="aObjectID"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginCreateReference(String aContainerID, String aObjectID, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionCreateReference, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateReference.InputParameter(inIndex++), aContainerID));
            invocation.AddInput(new ArgumentString((ParameterString)iActionCreateReference.InputParameter(inIndex++), aObjectID));
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionCreateReference.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aNewID"></param>
        public void EndCreateReference(IntPtr aAsyncHandle, out String aNewID)
        {
			uint code;
			string desc;
            if (Invocation.Error(aAsyncHandle, out code, out desc))
            {
                throw new ProxyError(code, desc);
            }
            uint index = 0;
            aNewID = Invocation.OutputString(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the SystemUpdateID state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgContentDirectory2 instance will not overlap.</remarks>
        /// <param name="aSystemUpdateIDChanged">The delegate to run when the state variable changes</param>
        public void SetPropertySystemUpdateIDChanged(System.Action aSystemUpdateIDChanged)
        {
            lock (iPropertyLock)
            {
                iSystemUpdateIDChanged = aSystemUpdateIDChanged;
            }
        }

        private void SystemUpdateIDPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iSystemUpdateIDChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the ContainerUpdateIDs state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgContentDirectory2 instance will not overlap.</remarks>
        /// <param name="aContainerUpdateIDsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyContainerUpdateIDsChanged(System.Action aContainerUpdateIDsChanged)
        {
            lock (iPropertyLock)
            {
                iContainerUpdateIDsChanged = aContainerUpdateIDsChanged;
            }
        }

        private void ContainerUpdateIDsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iContainerUpdateIDsChanged);
            }
        }

        /// <summary>
        /// Set a delegate to be run when the TransferIDs state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgContentDirectory2 instance will not overlap.</remarks>
        /// <param name="aTransferIDsChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyTransferIDsChanged(System.Action aTransferIDsChanged)
        {
            lock (iPropertyLock)
            {
                iTransferIDsChanged = aTransferIDsChanged;
            }
        }

        private void TransferIDsPropertyChanged()
        {
            lock (iPropertyLock)
            {
                ReportEvent(iTransferIDsChanged);
            }
        }

        /// <summary>
        /// Query the value of the SystemUpdateID property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the SystemUpdateID property</returns>
        public uint PropertySystemUpdateID()
        {
            PropertyReadLock();
            uint val = iSystemUpdateID.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the ContainerUpdateIDs property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the ContainerUpdateIDs property</returns>
        public String PropertyContainerUpdateIDs()
        {
            PropertyReadLock();
            String val = iContainerUpdateIDs.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the TransferIDs property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <returns>Value of the TransferIDs property</returns>
        public String PropertyTransferIDs()
        {
            PropertyReadLock();
            String val = iTransferIDs.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public void Dispose()
        {
            lock (this)
            {
                if (iHandle == IntPtr.Zero)
                    return;
                DisposeProxy();
                iHandle = IntPtr.Zero;
            }
            iActionGetSearchCapabilities.Dispose();
            iActionGetSortCapabilities.Dispose();
            iActionGetSortExtensionCapabilities.Dispose();
            iActionGetFeatureList.Dispose();
            iActionGetSystemUpdateID.Dispose();
            iActionBrowse.Dispose();
            iActionSearch.Dispose();
            iActionCreateObject.Dispose();
            iActionDestroyObject.Dispose();
            iActionUpdateObject.Dispose();
            iActionMoveObject.Dispose();
            iActionImportResource.Dispose();
            iActionExportResource.Dispose();
            iActionDeleteResource.Dispose();
            iActionStopTransferResource.Dispose();
            iActionGetTransferProgress.Dispose();
            iActionCreateReference.Dispose();
            iSystemUpdateID.Dispose();
            iContainerUpdateIDs.Dispose();
            iTransferIDs.Dispose();
        }
    }
}

