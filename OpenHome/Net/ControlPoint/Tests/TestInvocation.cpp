// Test for service/action invocation
// Builds a list of providers of the ConnectionManager service
// ... then checks how many times GetProtocolInfo can be run on each device in a second

#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/Discovery.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Net/Core/CpDevice.h>
#include <OpenHome/Net/Core/CpDeviceUpnp.h>
#include <OpenHome/Net/Private/Stack.h>
#include <OpenHome/OsWrapper.h>
#include <OpenHome/Net/Core/FunctorCpDevice.h>
#include <OpenHome/Net/Core/CpUpnpOrgConnectionManager1.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;

const TUint kDevicePollMs = 1000;
static TUint gActionCount = 0;


class DeviceListTI
{
public:
    DeviceListTI();
    ~DeviceListTI();
    void Stop();
    void TestSync();
    void Poll();
    TUint Count() const;
    void Added(CpDevice& aDevice);
    void Removed(CpDevice& aDevice);
private:
    void TimerExpired();
    void GetProtocolInfoComplete(IAsync& aAsync);
private:
    Mutex iLock;
    std::vector<CpDevice*> iList;
    TBool iStopped;
    Semaphore iPollStop;
    TUint iStopTimeMs;
    CpProxyUpnpOrgConnectionManager1* iConnMgr;
    Brh iExpectedSink;
};


DeviceListTI::DeviceListTI()
    : iLock("DLMX")
    , iStopped(false)
    , iPollStop("SDPS", 0)
{
}

DeviceListTI::~DeviceListTI()
{
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        iList[i]->RemoveRef();
        iList[i] = NULL;
    }
}

void DeviceListTI::Stop()
{
    iStopped = true;
}

void DeviceListTI::TestSync()
{
    // trivial validation of the sync wrappers to all APIs
    // single sync call to whichever device happens to be first in our list
    if (iList.size() == 0) {
        Print("No devices found, so nothing to test\n");
        return;
    }
    CpDevice* device = iList[0];
    Print("Sync call to device ");
    Print(device->Udn());
    Print("\n");
    iConnMgr = new CpProxyUpnpOrgConnectionManager1(*device);
    Brh source;
    Brh sink;
    try {
        iConnMgr->SyncGetProtocolInfo(source, sink);
    }
    catch(ProxyError) {}
#if 0
    Print("source is ");
    Print(source);
    Print("\nsink is ");
    Print(sink);
    Print("\n");
#endif
    delete iConnMgr;
}

void DeviceListTI::Poll()
{
    Timer timer(MakeFunctor(*this, &DeviceListTI::TimerExpired));
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceListTI::GetProtocolInfoComplete);
    Brh tmp;
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        TUint countBefore = gActionCount;
        Print("Device ");
        Print(device->Udn());
        iConnMgr = new CpProxyUpnpOrgConnectionManager1(*device);
        iStopTimeMs = Os::TimeInMs() + kDevicePollMs;
        timer.FireIn(kDevicePollMs);
        for (TUint j=0; j<Stack::InitParams().NumActionInvokerThreads(); j++) {
            iConnMgr->BeginGetProtocolInfo(callback);
        }
        iPollStop.Wait();
        Print("    %u\n", gActionCount - countBefore);
        delete iConnMgr;
        iExpectedSink.TransferTo(tmp);
    }
}

TUint DeviceListTI::Count() const
{
    return (TUint)iList.size();
}

void DeviceListTI::TimerExpired()
{
    iPollStop.Signal();
}

void DeviceListTI::GetProtocolInfoComplete(IAsync& aAsync)
{
    if (Os::TimeInMs() > iStopTimeMs) {
        return;
    }
    FunctorAsync callback = MakeFunctorAsync(*this, &DeviceListTI::GetProtocolInfoComplete);
    iConnMgr->BeginGetProtocolInfo(callback);

    Brh source;
    Brh sink;
    iConnMgr->EndGetProtocolInfo(aAsync, source, sink); // throws if invocation failed
    iLock.Wait();
    gActionCount++;
    if (sink.Bytes() == 0) {
        ASSERT(iExpectedSink.Bytes() == 0);
    }
    else {
        if (iExpectedSink.Bytes() == 0) {
            sink.TransferTo(iExpectedSink);
        }
        else {
            ASSERT(sink == iExpectedSink);
        }
    }
    iLock.Signal();
}

void DeviceListTI::Added(CpDevice& aDevice)
{
    AutoMutex a(iLock);
    if (!iStopped) {
        iList.push_back(&aDevice);
        ASSERT(aDevice==aDevice);
        ASSERT(!(aDevice!=aDevice));
        aDevice.AddRef();
    }
}

void DeviceListTI::Removed(CpDevice& aDevice)
{
    if (iStopped) {
        return;
    }

    AutoMutex a(iLock);
    const TUint count = (TUint)iList.size();
    for (TUint i=0; i<count; i++) {
        CpDevice* device = iList[i];
        if (device->Udn() == aDevice.Udn()) {
            iList[i] = NULL;
            iList.erase(iList.begin()+i);
            device->RemoveRef();
            break;
        }
    }
}


void TestInvocation()
{
    gActionCount = 0; // reset this here in case we're run multiple times via TestShell
    FunctorAsync dummy;
    /* Set an empty handler for errors to avoid test output being swamped by expected
       errors from invocations we interrupt at the end of each device's 1s timeslice */
    Stack::InitParams().SetAsyncErrorHandler(dummy);

    Debug::SetLevel(Debug::kNone);
    DeviceListTI* deviceList = new DeviceListTI;
    FunctorCpDevice added = MakeFunctorCpDevice(*deviceList, &DeviceListTI::Added);
    FunctorCpDevice removed = MakeFunctorCpDevice(*deviceList, &DeviceListTI::Removed);
    const Brn domainName("upnp.org");
    const Brn serviceType("ConnectionManager");
#if 1
    const TUint ver = 1;
    CpDeviceListUpnpServiceType* list =
                new CpDeviceListUpnpServiceType(domainName, serviceType, ver, added, removed);
#else
    const Brn uuid("7076436f-6e65-1063-8074-000da201f542");
    CpDeviceListUpnpUuid* list = new CpDeviceListUpnpUuid(uuid, added, removed);
#endif
    Blocker* blocker = new Blocker;
    blocker->Wait(Stack::InitParams().MsearchTimeSecs());
    delete blocker;
    deviceList->Stop();

    TUint startTime = Os::TimeInMs();
    //deviceList->TestSync();
    deviceList->Poll();

    const TUint count = deviceList->Count();
    Print("\n%u actions invoked on %u devices (avg %u) in %u seconds\n",
                        gActionCount, count, (count==0? 0 : gActionCount/count), (Os::TimeInMs()-startTime+500)/1000);

    delete list;
    delete deviceList;
}
