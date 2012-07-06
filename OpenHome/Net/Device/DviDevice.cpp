#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Net/Private/DviProtocolUpnp.h> // for DviProtocolUpnp ctor only
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/DviProviderSubscriptionLongPoll.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviDevice

const Brn DviDevice::kResourceDir("resource");

DviDevice::DviDevice(const Brx& aUdn)
    : iLock("DDVM")
    , iServiceLock("DVM2")
    , iResourceManager(NULL)
    , iShutdownSem("DVSD", 1)
{
    Construct(aUdn);
}

DviDevice::DviDevice(const Brx& aUdn, IResourceManager& aResourceManager)
    : iLock("DDVM")
    , iServiceLock("DVM2")
    , iResourceManager(&aResourceManager)
    , iShutdownSem("DVSD", 1)
{
    Construct(aUdn);
}

void DviDevice::Construct(const Brx& aUdn)
{
    Stack::AddObject(this);
    iRefCount = 1;
    iUdn.Set(aUdn);
    iEnabled = eDisabled;
    iConfigId = 0;
    iConfigUpdated = false;
    iParent = NULL;
    iProtocolDisableCount = 0;
    iSubscriptionId = 0;
    iProviderSubscriptionLongPoll = NULL;
    DviDeviceMap::Add(*this);
}

void DviDevice::AddProtocol(IDvProtocol* aProtocol)
{
    // Not threadsafe.  Assumed to be called only from ctor of derived devices
    iProtocols.push_back(aProtocol);
}

DviDevice::~DviDevice()
{
    Stack::RemoveObject(this);
}

void DviDevice::Destroy()
{
    iLock.Wait();
    DviDeviceMap::Remove(*this);
    for (TUint i=0; i<iDevices.size(); i++) {
        iDevices[i]->Destroy();
    }
    iDevices.clear();
    if (iEnabled == eEnabled) {
        Functor blank;
        SetDisabled(blank, true);
    }
    iLock.Signal();
    iShutdownSem.Wait();
    TUint i = 0;
    for (; i<(TUint)iProtocols.size(); i++) {
        delete iProtocols[i];
    }
    iServiceLock.Wait();
    for (i=0; i<iServices.size(); i++) {
        iServices[i]->StopSubscriptions();
        iServices[i]->RemoveRef();
    }
    iServices.clear();
    iServiceLock.Signal();
    delete iProviderSubscriptionLongPoll;
    RemoveWeakRef();
}

void DviDevice::AddWeakRef()
{
    iLock.Wait();
    iRefCount++;
    iLock.Signal();
}

void DviDevice::RemoveWeakRef()
{
    iLock.Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    iLock.Signal();
    if (dead) {
        delete this;
    }
}

const Brx& DviDevice::Udn() const
{
    return iUdn;
}

TBool DviDevice::Enabled() const
{
    iLock.Wait();
    TBool enabled = (iEnabled==eEnabled);
    iLock.Signal();
    return enabled;
}

void DviDevice::SetEnabled()
{
    ASSERT(iEnabled != eEnabled);
    iLock.Wait();
    if (iProtocolDisableCount != 0) {
        // We're in the unusual situation of having the client Enable this device while its in the process of disabling.
        // It'd be potentially fiddly for each protocol to halt a disable.
        // ...so we prefer to waste a little time but avoid complex code by waiting for the disable to complete
        iDisableComplete = MakeFunctor(*this, &DviDevice::DisableComplete);
        iLock.Signal();
        iShutdownSem.Wait();
        iLock.Wait();
    }
    iEnabled = eEnabled;
    iConfigUpdated = false;
    iShutdownSem.Clear();
    iLock.Signal();
    TUint i;
    for (i=0; i<(TUint)iProtocols.size(); i++) {
        iProtocols[i]->Enable();
    }
    // queue updates for all service properties
    // nothing may have changed but individual subscriptions will spot this and skip any update message
    for (i=0; i<iServices.size(); i++) {
        iServices[i]->Enable();
        iServices[i]->PublishPropertyUpdates();
    }
}

void DviDevice::SetDisabled(Functor aCompleted)
{
    SetDisabled(aCompleted, false);
}

void DviDevice::GetAttribute(const TChar* aKey, const TChar** aValue) const
{
    Brn key(aKey);
    Parser parser(key);
    Brn name = parser.Next('.');
    for (TUint i=0; i<(TUint)iProtocols.size(); i++) {
        IDvProtocol* protocol = iProtocols[i];
        if (protocol->ProtocolName() == name) {
            aKey += name.Bytes() + 1;
            protocol->GetAttribute(aKey, aValue);
            return;
        }
    }
    *aValue = NULL;
}

void DviDevice::SetAttribute(const TChar* aKey, const TChar* aValue)
{
    Brn key(aKey);
    Parser parser(key);
    Brn name = parser.Next('.');
    aKey += name.Bytes() + 1;
    // assume keys starting 'Test' are a special case which can be updated at any time
    if (strlen(aKey) < 4 || strncmp(aKey, "Test", 4) != 0) {
        ASSERT(iEnabled == eDisabled);
    }
    if (name == Brn("Core")) {
        static const char* longPollEnable = "LongPollEnable";
        if (iProviderSubscriptionLongPoll == NULL && 
            strncmp(aKey, longPollEnable, sizeof(longPollEnable)-1) == 0) {
            iProviderSubscriptionLongPoll = new DviProviderSubscriptionLongPoll(*this);
            ConfigChanged();
        }
    }
    else {
        for (TUint i=0; i<(TUint)iProtocols.size(); i++) {
            IDvProtocol* protocol = iProtocols[i];
            if (protocol->ProtocolName() == name) {
                protocol->SetAttribute(aKey, aValue);
                ConfigChanged();
                break;
            }
        }
    }
}

void DviDevice::AddService(DviService* aService)
{
    ASSERT(iEnabled == eDisabled);
    ASSERT(!Root()->HasService(aService->ServiceType()));
    iServices.push_back(aService);
    aService->AddRef();
    ConfigChanged();
}

TUint DviDevice::ServiceCount() const
{
    return (TUint)iServices.size();
}

DviService& DviDevice::Service(TUint aIndex) const
{
    ASSERT(aIndex < ServiceCount());
    return *(iServices[aIndex]);
}

DviService* DviDevice::ServiceReference(const ServiceType& aServiceType)
{
    DviService* service = NULL;
    iServiceLock.Wait();
    const Brx& fullNameUpnp = aServiceType.FullNameUpnp();
    const TUint count = (TUint)iServices.size();
    for (TUint i=0; i<count; i++) {
        DviService* s = iServices[i];
        if (s->ServiceType().FullNameUpnp() == fullNameUpnp) {
            s->AddRef();
            service = s;
            break;
        }
    }
    iServiceLock.Signal();
    return service;
}

void DviDevice::AddDevice(DviDevice* aDevice)
{
    ASSERT(!Enabled());
    iDevices.push_back(aDevice);
    aDevice->SetParent(this);
    ConfigChanged();
}

TUint DviDevice::DeviceCount() const
{
    return (TUint)iDevices.size();
}

DviDevice& DviDevice::Device(TUint aIndex) const
{
    ASSERT(aIndex < DeviceCount());
    return *(iDevices[aIndex]);
}

TBool DviDevice::IsRoot() const
{
    DviDevice* root = Root();
    return (root == this);
}

void DviDevice::WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    Parser parser(aUriTail);
    Brn dir = parser.Next('/');
    if (dir == kResourceDir) {
        if (iResourceManager != NULL) {
            iResourceManager->WriteResource(parser.Remaining(), aInterface, aLanguageList, aResourceWriter);
        }
    }
    else {
        for (TUint i=0; i<(TUint)iProtocols.size(); i++) {
            IDvProtocol* protocol = iProtocols[i];
            if (protocol->ProtocolName() == dir) {
                protocol->WriteResource(parser.Remaining(), aInterface, aLanguageList, aResourceWriter);
                break;
            }
        }
    }
}

void DviDevice::GetUriBase(Bwx& aUriBase, TIpAddress aInterface, TUint aPort, IDvProtocol& aProtocol)
{
    const Brx& name = aProtocol.ProtocolName();
    aUriBase.Append(Http::kUriPrefix);
    Endpoint endpt(aPort, aInterface);
    Endpoint::EndpointBuf buf;
    endpt.AppendEndpoint(buf);
    aUriBase.Append(buf);
    aUriBase.Append('/');
    Uri::Escape(aUriBase, iUdn);
    aUriBase.Append('/');
    aUriBase.Append(name);
    aUriBase.Append('/');
}

TUint DviDevice::ConfigId()
{
    return iConfigId;
}

void DviDevice::CreateSid(Brh& aSid)
{
    Bwh sid(iUdn.Bytes() + 1 + Ascii::kMaxUintStringBytes + 1);
    sid.Append(iUdn);
    sid.Append('-');
    Bws<Ascii::kMaxUintStringBytes> buf;
    iLock.Wait();
    (void)Ascii::AppendDec(buf, iSubscriptionId++);
    iLock.Signal();
    sid.Append(buf);
    sid.PtrZ();
    sid.TransferTo(aSid);
}

IResourceManager* DviDevice::ResourceManager()
{
    return iResourceManager;
}

void DviDevice::SetCustomData(const TChar* aProtocol, const TChar* aTag, void* aData)
{
    Brn protocolName(aProtocol);
    for (TUint i=0; i<(TUint)iProtocols.size(); i++) {
        IDvProtocol* protocol = iProtocols[i];
        if (protocol->ProtocolName() == protocolName) {
            protocol->SetCustomData(aTag, aData);
            break;
        }
    }
}

void DviDevice::GetResourceManagerUri(const NetworkAdapter& aAdapter, Brh& aUri)
{
    Brn protocolName("Upnp"); // FIXME
    for (TUint i=0; i<(TUint)iProtocols.size(); i++) {
        IDvProtocol* protocol = iProtocols[i];
        if (protocol->ProtocolName() == protocolName) {
            protocol->GetResourceManagerUri(aAdapter, aUri);
            break;
        }
    }
}

void DviDevice::SetParent(DviDevice* aParent)
{
    ASSERT(!Enabled());
    ASSERT(this != aParent);
    ASSERT(this != aParent->Root());
    iParent = aParent;
}

DviDevice* DviDevice::Root() const
{
    const DviDevice* root = this;
    while (root->iParent != NULL) {
        root = root->iParent;
    }
    return const_cast<DviDevice*>(root);
}

void DviDevice::SetDisabled(Functor aCompleted, bool aLocked)
{
    if (!aLocked) {
        iLock.Wait();
    }
    iDisableComplete = aCompleted;
    switch (iEnabled)
    {
    case eDisabled:
        iProtocolDisableCount = 0;
        break;
    case eDisabling:
        ASSERTS();
        break;
    case eEnabled:
        iEnabled = eDisabling;
        iProtocolDisableCount = (TUint)iProtocols.size();
        break;
    }
    if (!aLocked) {
        iLock.Signal();
    }
    if (iProtocolDisableCount == 0) {
        if (iDisableComplete) {
            iDisableComplete();
        }
        iShutdownSem.Signal();
    }
    else {
        Functor functor = MakeFunctor(*this, &DviDevice::ProtocolDisabled);
        for (TUint i=0; i<iProtocols.size(); i++) {
            iProtocols[i]->Disable(functor);
        }
    }
    // Tell services not to accept further action invocations
    for (TUint i=0; i<iServices.size(); i++) {
        iServices[i]->Disable();
    }
}

void DviDevice::ProtocolDisabled()
{
    iLock.Wait();
    ASSERT(iProtocolDisableCount != 0);
    if (--iProtocolDisableCount == 0) {
        iEnabled = eDisabled;
        if (iDisableComplete) {
            iDisableComplete();
        }
        iShutdownSem.Signal();
    }
    iLock.Signal();
}

void DviDevice::DisableComplete()
{
    iShutdownSem.Signal();
}

TBool DviDevice::HasService(const OpenHome::Net::ServiceType& aServiceType) const
{
    for (TUint i=0; i<iServices.size(); i++) {
        const OpenHome::Net::ServiceType& serviceType = iServices[i]->ServiceType();
        if (serviceType.Version() == aServiceType.Version() &&
            serviceType.Domain()  == aServiceType.Domain() &&
            serviceType.Name()    == aServiceType.Name()) {
            return true;
        }
    }
    return ChildHasService(aServiceType);
}

TBool DviDevice::ChildHasService(const OpenHome::Net::ServiceType& aServiceType) const
{
    for (TUint i=0; i<iDevices.size(); i++) {
        if (iDevices[i]->HasService(aServiceType)) {
            return true;
        }
    }
    return false;
}

void DviDevice::ConfigChanged()
{
    if (!iConfigUpdated) {
        iConfigId++;
        iConfigUpdated = true;
    }
}

TUint DviDevice::SubscriptionId()
{
    iLock.Wait();
    TUint id = iSubscriptionId++;
    iLock.Signal();
    return id;
}

void DviDevice::ListObjectDetails() const
{
    Log::Print("  DviDevice: addr=%p, udn=", this);
    Log::Print(iUdn);
    Log::Print(", refCount=%u\n", iRefCount);
}


// AttributeMap

AttributeMap::AttributeMap()
    : iLock("ATRM")
{
}

AttributeMap::~AttributeMap()
{
    Map::iterator it = iMap.begin();
    while (it != iMap.end()) {
        delete it->second;
        it++;
    }
}

const TChar* AttributeMap::Get(const TChar* aKey) const
{
    AutoMutex a(iLock);
    Brn key(aKey);
    Map::const_iterator it = iMap.find(key);
    if (it == iMap.end()) {
        return NULL;
    }
    AttributeMap::Attribute* attr = it->second;
    return attr->Value();
}

void AttributeMap::Set(const TChar* aKey, const TChar* aValue)
{
    iLock.Wait();
    Brn key(aKey);
    Map::iterator it = iMap.find(key);
    if (it != iMap.end()) {
        it->second->UpdateValue(aValue);
    }
    else {
        AttributeMap::Attribute* attr = new AttributeMap::Attribute(aKey, aValue);
        iMap.insert(std::pair<Brn, AttributeMap::Attribute*>(attr->Key(), attr));
    }
    iLock.Signal();
}


// DviDeviceStandard

DviDeviceStandard::DviDeviceStandard(const Brx& aUdn)
    : DviDevice(aUdn)
{
    Construct();
}

DviDeviceStandard::DviDeviceStandard(const Brx& aUdn, IResourceManager& aResourceManager)
    : DviDevice(aUdn, aResourceManager)
{
    Construct();
}

void DviDeviceStandard::Construct()
{
    AddProtocol(new DviProtocolUpnp(*this));
}


// AttributeMap::Attribute

AttributeMap::Attribute::Attribute(const TChar* aKey, const TChar* aValue)
    : iKey(aKey)
    , iValue(aValue)
{
}

Brn AttributeMap::Attribute::Key() const
{
    Brn buf(iKey);
    return buf;
}

const TChar* AttributeMap::Attribute::Value() const
{
    return iValue.CString();
}

void AttributeMap::Attribute::UpdateValue(const TChar* aValue)
{
    iValue.Set(aValue);
}


// DviDeviceMap

DviDeviceMap::DviDeviceMap()
    : iLock("DVDM")
{
}

DviDeviceMap::~DviDeviceMap()
{
}

void DviDeviceMap::Add(DviDevice& aDevice)
{
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aDevice.Udn());
    self.iMap.insert(std::pair<Brn,DviDevice*>(udn, &aDevice));
    self.iLock.Signal();
}

void DviDeviceMap::Remove(DviDevice& aDevice)
{
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aDevice.Udn());
    Map::iterator it = self.iMap.find(udn);
    if (it != self.iMap.end()) {
        self.iMap.erase(it);
    }
    self.iLock.Signal();
}

DviDevice* DviDeviceMap::Find(const Brx& aUdn)
{
    DviDevice* device = NULL;
    DviDeviceMap& self = DviStack::DeviceMap();
    self.iLock.Wait();
    Brn udn(aUdn);
    Map::iterator it = self.iMap.find(udn);
    if (it != self.iMap.end()) {
        device = it->second;
    }
    self.iLock.Signal();
    return device;
}

void DviDeviceMap::WriteResource(const Brx& aUriTail, TIpAddress aInterface, std::vector<char*>& aLanguageList, IResourceWriter& aResourceWriter)
{
    iLock.Wait();
    Parser parser(aUriTail);
    (void)parser.Next('/'); // skip leading slash
    Brn dir = parser.Next('/');
    if (dir.Bytes() > 0) {
        Map::iterator it = iMap.find(dir);
        if (it != iMap.end()) {
            DviDevice* device = it->second;
            iLock.Signal();
            device->WriteResource(parser.Remaining(), aInterface, aLanguageList, aResourceWriter);
            return;
        }
    }
    iLock.Signal();
}
