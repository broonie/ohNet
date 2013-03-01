#include <OpenHome/Net/Private/CpiDevice.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/CpiStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// CpiDevice

CpiDevice::CpiDevice(OpenHome::Net::CpStack& aCpStack, const Brx& aUdn, ICpiProtocol& aProtocol, ICpiDeviceObserver& aObserver, void* aOwnerData)
    : iCpStack(aCpStack)
    , iUdn(aUdn)
    , iLock("CDVM")
    , iProtocol(aProtocol)
    , iObserver(aObserver)
    , iOwnerData(aOwnerData)
    , iRefCount(1)
    , iReady(false)
    , iExpired(false)
    , iRemoved(false)
{
    iCpStack.Env().AddObject(this);
}

const Brx& CpiDevice::Udn() const
{
    return iUdn;
}

const TChar* CpiDevice::UdnAsCString() const
{
    return iUdn.CString();
}

TBool CpiDevice::operator==(const CpiDevice& aDevice) const
{
    return (&aDevice == this);
}

TBool CpiDevice::operator!=(const CpiDevice& aDevice) const
{
    return (&aDevice != this);
}

CpStack& CpiDevice::GetCpStack()
{
    return iCpStack;
}

void* CpiDevice::OwnerData()
{
    return iOwnerData;
}

void CpiDevice::AddRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void CpiDevice::RemoveRef()
{
    TBool dead;
    iLock.Wait();
    dead = (--iRefCount <= 0);
    iLock.Signal();
    if (dead) {
        iObserver.Release();
        delete this;
    }
}

TBool CpiDevice::GetAttribute(const char* aKey, Brh& aValue) const
{
    return iProtocol.GetAttribute(aKey, aValue);
}

void CpiDevice::InvokeAction(Invocation& aInvocation)
{
    iProtocol.InvokeAction(aInvocation);
}

TUint CpiDevice::Subscribe(CpiSubscription& aSubscription, const Uri& aSubscriber)
{
    return iProtocol.Subscribe(aSubscription, aSubscriber);
}

TUint CpiDevice::Renew(CpiSubscription& aSubscription)
{
    return iProtocol.Renew(aSubscription);
}

void CpiDevice::Unsubscribe(CpiSubscription& aSubscription, const Brx& aSid)
{
    iProtocol.Unsubscribe(aSubscription, aSid);
}

void CpiDevice::NotifyRemovedBeforeReady()
{
    iProtocol.NotifyRemovedBeforeReady();
}

void CpiDevice::SetReady()
{
    iReady = true;
}

TBool CpiDevice::IsReady() const
{
    return iReady;
}

void CpiDevice::SetExpired(TBool aExpired)
{
    iExpired = aExpired;
}

TBool CpiDevice::HasExpired() const
{
    return iExpired;
}

void CpiDevice::SetRemoved()
{
    iRemoved = true;
}

TBool CpiDevice::IsRemoved() const
{
    return iRemoved;
}

void CpiDevice::ListObjectDetails() const
{
    Log::Print("  CpiDevice: addr=%p, udn=", this);
    Log::Print(iUdn);
    Log::Print(", refCount=%u\n", iRefCount);
}

CpiDevice::~CpiDevice()
{
    LOG(kDevice, "~CpiDevice for device ");
    LOG(kDevice, iUdn);
    LOG(kDevice, "\n");
    ASSERT(iRefCount == 0);
    iCpStack.Env().RemoveObject(this);
}


// CpiDeviceList

void CpiDeviceList::Refresh()
{
}

CpiDevice* CpiDeviceList::RefDevice(const Brx& aUdn)
{
    AutoMutex a(iLock);
    return RefDeviceLocked(aUdn);
}

CpiDevice* CpiDeviceList::RefDeviceLocked(const Brx& aUdn)
{
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        return NULL;
    }
    CpiDevice* device = it->second;
    device->AddRef();
    return device;
}

CpiDeviceList::CpiDeviceList(CpStack& aCpStack, FunctorCpiDevice aAdded, FunctorCpiDevice aRemoved)
    : iCpStack(aCpStack)
    , iActive(false)
    , iRefreshing(false)
    , iLock("CDLM")
    , iAdded(aAdded)
    , iRemoved(aRemoved)
    , iRefCount(0)
    , iShutdownSem("CDLS", 0)
{
    ASSERT(iAdded);
    ASSERT(iRemoved);
    iCpStack.Env().AddObject(this);
}

CpiDeviceList::~CpiDeviceList()
{
    TBool wait = false;
    Mutex& lock = iCpStack.Env().Mutex();
    lock.Wait();
    if (iRefCount > 0) {
        wait = true;
        iShutdownSem.Clear();
    }
    lock.Signal();
    if (wait) {
        iShutdownSem.Wait();
    }
    ClearMap(iMap);
    ClearMap(iRefreshMap);
    iCpStack.Env().RemoveObject(this);
}

void CpiDeviceList::Add(CpiDevice* aDevice)
{
    LOG(kDevice, "CpiDeviceList::Add for device ");
    LOG(kDevice, aDevice->Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (aDevice->HasExpired() || !iActive) {
        LOG(kDevice, "< CpiDeviceList::Add, device expired or list stopped\n");
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    if (iRefreshing) {
        Brn udn(aDevice->Udn());
        Map::iterator it = iRefreshMap.find(udn);
        if (it == iRefreshMap.end()) {
            iRefreshMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
            aDevice->AddRef(); // for refresh list
        }
    }
    CpiDevice* tmp = RefDeviceLocked(aDevice->Udn());
    if (tmp != NULL) {
        // device is already in the list, ignore this call to Add()
        LOG(kDevice, "< CpiDeviceList::Add, device ");
        LOG(kDevice, aDevice->Udn());
        LOG(kDevice, " already in list\n");
        tmp->RemoveRef();
        aDevice->RemoveRef();
        iLock.Signal();
        return;
    }
    Brn udn(aDevice->Udn());
    iMap.insert(std::pair<Brn,CpiDevice*>(udn, aDevice));
    aDevice->AddRef(); // for observer
    iLock.Signal();
    if (IsDeviceReady(*aDevice)) {
        SetDeviceReady(*aDevice);
    }
    aDevice->RemoveRef(); // observer's ref
}

void CpiDeviceList::Remove(const Brx& aUdn)
{
    iLock.Wait();
    Brn udn(aUdn);
    Map::iterator it = iMap.find(udn);
    if (it == iMap.end()) {
        // device isn't in this list
        iLock.Signal();
        return;
    }
    CpiDevice* device = RefDeviceLocked(aUdn);
    iMap.erase(it);
    iPendingRemove.push_back(device);
    iCpStack.DeviceListUpdater().QueueRemoved(*this, *device);
    device->RemoveRef();
    iLock.Signal();
}

TBool CpiDeviceList::IsDeviceReady(CpiDevice& /*aDevice*/)
{
    return true;
}

TBool CpiDeviceList::StartRefresh()
{
    TBool refreshAlreadyInProgress;
    iLock.Wait();
    refreshAlreadyInProgress = iRefreshing;
    iRefreshing = true;
    iLock.Signal();
    return refreshAlreadyInProgress;
}

void CpiDeviceList::RefreshComplete()
{
    iCpStack.DeviceListUpdater().QueueRefreshed(*this);
}

void CpiDeviceList::CancelRefresh()
{
    iRefreshing = false;
    ClearMap(iRefreshMap);
}

void CpiDeviceList::SetDeviceReady(CpiDevice& aDevice)
{
    aDevice.SetReady();
    iCpStack.DeviceListUpdater().QueueAdded(*this, aDevice);
}

void CpiDeviceList::ClearMap(Map& aMap)
{
    Map::iterator it = aMap.begin();
    while (it != aMap.end()) {
        it->second->RemoveRef();
        it->second = NULL;
        it++;
    }
    aMap.clear();
}

void CpiDeviceList::AddRef()
{
    iCpStack.Env().Mutex().Wait();
    ++iRefCount;
    iCpStack.Env().Mutex().Signal();
}

void CpiDeviceList::RemoveRef()
{
    Mutex& lock = iCpStack.Env().Mutex();
    lock.Wait();
    if (--iRefCount == 0) {
        iShutdownSem.Signal();
    }
    lock.Signal();
}

void CpiDeviceList::NotifyAdded(CpiDevice& aDevice)
{
    LOG(kDevice, "CpiDeviceList::NotifyAdded for device ");
    LOG(kDevice, aDevice.Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    if (!iActive) {
        iLock.Signal();
        return;
    }
    CpiDevice* device = RefDeviceLocked(aDevice.Udn());
    if (device == NULL) {
        // aDevice must have been removed since we queued the Added event
        iLock.Signal();
        return;
    }
    TBool sameDevice = ((void*)device == (void*)&aDevice);
    device->RemoveRef();
    if (!sameDevice) {
        // aDevice has been replaced, probably because its location changed
        iLock.Signal();
        return;
    }
    iLock.Signal();
    LOG(kTrace, "Device+ {udn{");
    LOG(kTrace, aDevice.Udn());
    LOG(kTrace, "}}\n");
    iAdded(aDevice);
}

void CpiDeviceList::NotifyRemoved(CpiDevice& aDevice)
{
    (void)DoRemove(aDevice);
}

TBool CpiDeviceList::DoRemove(CpiDevice& aDevice)
{
    LOG(kDevice, "> CpiDeviceList::DoRemove for device ");
    LOG(kDevice, aDevice.Udn());
    LOG(kDevice, "\n");
    iLock.Wait();
    TBool found = false;
    for (TUint i=0; i<(TUint)iPendingRemove.size(); i++) {
        if ((void*)iPendingRemove[i] == (void*)&aDevice) {
            iPendingRemove.erase(iPendingRemove.begin() + i);
            found = true;
            break;
        }
    }
    if (!found) {
        // device isn't in this list
        LOG(kDevice, "< CpiDeviceList::DoRemove, device not in list\n");
        iLock.Signal();
        return false;
    }
    if (!aDevice.IsReady()) {
        iLock.Signal();
        aDevice.NotifyRemovedBeforeReady();
        iLock.Wait();
    }
    // don't remove our ref to the device yet, re-use it for the observer
    TBool callObserver = (iActive && aDevice.IsReady());
    iLock.Signal();
    if (callObserver) {
        iRemoved(aDevice);
    }
    LOG(kTrace, "Device-  {udn{");
    LOG(kTrace, aDevice.Udn());
    LOG(kTrace, "}}\n");
    aDevice.RemoveRef();
    return true;
}

void CpiDeviceList::NotifyRefreshed()
{
    iLock.Wait();
    iRefreshing = false;
    if (iActive) {
        /* map iterator is invalidated by removing an item so we'll need to iterate once per removal
           assume that the 0.5 * O(n^2) ish cost is bearable as refresh is a rare operation which
           can only feasibly run once ever few seconds in the worst possible case */
        Map::iterator it = iMap.begin();
        while (it != iMap.end()) {
            Map::iterator found = iRefreshMap.find(it->first);
            if (found != iRefreshMap.end()) {
                // device still exists
                it++;
            }
            else {
                CpiDevice* device = it->second;
                // skip devices which aren't ready yet
                // ...assume that they'll either become ready or will be removed via other routes in time
                // Upnp lists don't cope with devices being removed in this state
                if (!device->IsReady()) {
                    it++;
                }
                else {
                    device->AddRef();
                    iLock.Signal();
                    TBool removed = DoRemove(*device);
                    device->RemoveRef();
                    iLock.Wait();
                    if (removed) {
                       it = iMap.begin();
                    }
                    else {
                        it++;
                    }
                }
            }
        }
    }
    ClearMap(iRefreshMap);
    iLock.Signal();
}

void CpiDeviceList::ListObjectDetails() const
{
    Log::Print("  CpiDeviceList: addr=%p\n", this);
}


// CpiDeviceListUpdater

CpiDeviceListUpdater::CpiDeviceListUpdater()
    : Thread("DLUP")
    , iLock("DLUM")
{
    Start();
}

CpiDeviceListUpdater::~CpiDeviceListUpdater()
{
    Kill();
    Join();
    while (iList.size() > 0) {
        iLock.Wait();
        UpdateBase* update = iList.front();
        iList.pop_front();
        iLock.Signal();
        delete update;
    }
}

void CpiDeviceListUpdater::QueueAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
{
    Queue(new UpdateAdded(aUpdater, aDevice));
}

void CpiDeviceListUpdater::QueueRemoved(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
{
    CpiDeviceListUpdater::Queue(new UpdateRemoved(aUpdater, aDevice));
}

void CpiDeviceListUpdater::QueueRefreshed(IDeviceListUpdater& aUpdater)
{
    Queue(new UpdateRefresh(aUpdater));
}

void CpiDeviceListUpdater::Queue(UpdateBase* aUpdate)
{
    iLock.Wait();
    iList.push_back(aUpdate);
    iLock.Signal();
    Signal();
}

void CpiDeviceListUpdater::Run()
{
    for (;;) {
        Wait();
        iLock.Wait();
        UpdateBase* update = iList.front();
        iList.pop_front();
        iLock.Signal();
        update->Update();
        delete update;
    }
}


// CpiDeviceListUpdater::UpdateBase

CpiDeviceListUpdater::UpdateBase::~UpdateBase()
{
    iUpdater.RemoveRef();
}

CpiDeviceListUpdater::UpdateBase::UpdateBase(IDeviceListUpdater& aUpdater)
    : iUpdater(aUpdater)
{
    iUpdater.AddRef();
}


// CpiDeviceListUpdater::UpdateAdded

CpiDeviceListUpdater::UpdateAdded::UpdateAdded(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
    , iDevice(aDevice)
{
    iDevice.AddRef();
}

CpiDeviceListUpdater::UpdateAdded::~UpdateAdded()
{
    iDevice.RemoveRef();
}

void CpiDeviceListUpdater::UpdateAdded::Update()
{
    iUpdater.NotifyAdded(iDevice);
}


// CpiDeviceListUpdater::UpdateRemoved

CpiDeviceListUpdater::UpdateRemoved::UpdateRemoved(IDeviceListUpdater& aUpdater, CpiDevice& aDevice)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
    , iDevice(aDevice)
{
    iDevice.AddRef();
}

CpiDeviceListUpdater::UpdateRemoved::~UpdateRemoved()
{
    iDevice.RemoveRef();
}

void CpiDeviceListUpdater::UpdateRemoved::Update()
{
    iUpdater.NotifyRemoved(iDevice);
}


// CpiDeviceListUpdater::UpdateRefresh

CpiDeviceListUpdater::UpdateRefresh::UpdateRefresh(IDeviceListUpdater& aUpdater)
    : CpiDeviceListUpdater::UpdateBase(aUpdater)
{
}

void CpiDeviceListUpdater::UpdateRefresh::Update()
{
    iUpdater.NotifyRefreshed();
}
