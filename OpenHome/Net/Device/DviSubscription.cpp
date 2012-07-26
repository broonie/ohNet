#include <OpenHome/Net/Private/DviSubscription.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviService.h>
#include <OpenHome/Net/Private/Service.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Functor.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Converter.h>

#include <vector>
#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// AutoPropertiesLock

class AutoPropertiesLock : INonCopyable
{
public:
    AutoPropertiesLock(DviService& aService);
    ~AutoPropertiesLock();
private:
    DviService& iService;
};

AutoPropertiesLock::AutoPropertiesLock(DviService& aService)
    : iService(aService)
{
    iService.PropertiesLock();
}

AutoPropertiesLock::~AutoPropertiesLock()
{
    iService.PropertiesUnlock();
}


// DviSubscription

DviSubscription::DviSubscription(DviDevice& aDevice, IPropertyWriterFactory& aWriterFactory,
                                 IDviSubscriptionUserData* aUserData, Brh& aSid, TUint& aDurationSecs)
    : iLock("MDSB")
    , iRefCount(1)
    , iDevice(aDevice)
    , iWriterFactory(aWriterFactory)
    , iUserData(aUserData)
    , iService(NULL)
    , iSequenceNumber(0)
{
    iDevice.AddWeakRef();
    aSid.TransferTo(iSid);
    Functor functor = MakeFunctor(*this, &DviSubscription::Expired);
    iTimer = new Timer(functor);
    DoRenew(aDurationSecs);
}

void DviSubscription::Start(DviService& aService)
{
    iService = &aService;
    iService->AddRef();
    const DviService::VectorProperties& properties = iService->Properties();
    for (TUint i=0; i<properties.size(); i++) {
        // store all seq nums as 0 initially to ensure all are published by the first call to WriteChanges()
        iPropertySequenceNumbers.push_back(0);
        ASSERT(properties[i] != 0);
    }
}

void DviSubscription::Stop()
{
    iLock.Wait();
    iTimer->Cancel();
    if (iService != NULL) {
        iService->RemoveRef();
        iService = NULL;
    }
    iLock.Signal();
    iWriterFactory.NotifySubscriptionExpired(iSid);
}

void DviSubscription::AddRef()
{
    Stack::Mutex().Wait();
    iRefCount++;
    Stack::Mutex().Signal();
}

TBool DviSubscription::TryAddRef()
{
    TBool added = false;
    Stack::Mutex().Wait();
    if (iRefCount != 0) {
        iRefCount++;
        added = true;
    }
    Stack::Mutex().Signal();
    return added;
}

void DviSubscription::RemoveRef()
{
    Stack::Mutex().Wait();
    iRefCount--;
    TBool dead = (iRefCount == 0);
    Stack::Mutex().Signal();
    if (dead) {
        delete this;
    }
}

void DviSubscription::Remove()
{
    iLock.Wait();
    DviService* service = iService;
    if (service != NULL) {
        service->AddRef();
    }
    iLock.Signal();
    if (service != NULL) {
        service->RemoveSubscription(iSid);
        service->RemoveRef();
    }
}

void DviSubscription::Renew(TUint& aSeconds)
{
    iLock.Wait();
    TBool expired = (iService == NULL);
    iLock.Signal();
    if (expired) {
        THROW(DvSubscriptionError);
    }
    DoRenew(aSeconds);
}

void DviSubscription::DoRenew(TUint& aSeconds)
{
    const TUint maxDuration = Stack::InitParams().DvMaxUpdateTimeSecs();
    if (aSeconds == 0 || aSeconds > maxDuration) {
        aSeconds = maxDuration;
    }
    iTimer->FireIn(aSeconds * 1000);
}

void DviSubscription::WriteChanges()
{
    IPropertyWriter* writer = NULL;
    try {
        writer = CreateWriter();
        if (writer != NULL) {
            writer->PropertyWriteEnd();
            delete writer;
        }
    }
    catch(NetworkTimeout&) {
        // we may block a publisher for a relatively long time failing to connect
        // its reasonable to assume that later attempts are also likely to fail
        // ...so its better if we don't keep blocking and instead remove the subscription
        Remove();
    }
    catch(NetworkError&) {}
    catch(HttpError&) {}
    catch(WriterError&) {}
    catch(ReaderError&) {}
}

IPropertyWriter* DviSubscription::CreateWriter()
{
    AutoMutex a(iLock);
    LOG(kDvEvent, "WriteChanges for subscription ");
    LOG(kDvEvent, iSid);
    LOG(kDvEvent, " seq - %u\n", iSequenceNumber);
    if (!iDevice.Enabled()) {
        LOG(kDvEvent, "Device disabled; defer publishing changes\n");
        return NULL;
    }

    if (iService == NULL) {
        LOG(kDvEvent, "Subscription stopped; don't publish changes\n");
        return NULL;
    }
    AutoPropertiesLock b(*iService);
    IPropertyWriter* writer = NULL;
    const DviService::VectorProperties& properties = iService->Properties();
    ASSERT(properties.size() == iPropertySequenceNumbers.size()); // services can't change definition after first advertisement
    for (TUint i=0; i<properties.size(); i++) {
        Property* prop = properties[i];
        TUint seq = prop->SequenceNumber();
        ASSERT(seq != 0); // => implementor hasn't initialised the property
        if (seq != iPropertySequenceNumbers[i]) {
            if (writer == NULL) {
                writer = iWriterFactory.CreateWriter(iUserData, iSid, iSequenceNumber);
                if (writer == NULL) {
                    THROW(WriterError);
                }
                if (iSequenceNumber == UINT32_MAX) {
                    iSequenceNumber = 1;
                }
                else {
                    iSequenceNumber++;
                }
            }
            prop->Write(*writer);
            iPropertySequenceNumbers[i] = seq;
        }
    }
    if (writer == NULL) {
        LOG(kDvEvent, "Found no changes to publish\n");
    }
    return writer;
}

const Brx& DviSubscription::Sid() const
{
    return iSid;
}

TBool DviSubscription::PropertiesInitialised() const
{
    TBool initialised = true;
    iLock.Wait();
    if (iService != NULL) {
        const DviService::VectorProperties& properties = iService->Properties();
        for (TUint i=0; i<properties.size(); i++) {
            if (properties[i] == 0) {
                initialised = false;
                break;
            }
        }
    }
    iLock.Signal();
    return initialised;
}

DviSubscription::~DviSubscription()
{
    iLock.Wait();
    if (iService != NULL) {
        iService->RemoveRef();
    }
    iLock.Signal();
    iWriterFactory.NotifySubscriptionDeleted(iSid);
    iDevice.RemoveWeakRef();
    delete iTimer;
    if (iUserData != NULL) {
        iUserData->Release();
    }
}

void DviSubscription::Expired()
{
    // no need to call NotifySubscriptionExpired - line below calls back into Stop() which performs the notification
    iService->RemoveSubscription(iSid);
}


// PropertyWriter

PropertyWriter::PropertyWriter()
    : iWriter(NULL)
{
}

void PropertyWriter::SetWriter(IWriter& aWriter)
{
    iWriter = &aWriter;
}

void PropertyWriter::WriteVariable(IWriter& aWriter, const Brx& aName, const Brx& aValue)
{ // static
    aWriter.Write(Brn("<e:property>"));
    aWriter.Write('<');
    aWriter.Write(aName);
    aWriter.Write('>');
    aWriter.Write(aValue);
    aWriter.Write(Brn("</"));
    aWriter.Write(aName);
    aWriter.Write('>');
    aWriter.Write(Brn("</e:property>"));
}

void PropertyWriter::PropertyWriteString(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToXmlEscaped(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteInt(const Brx& aName, TInt aValue)
{
    Bws<Ascii::kMaxIntStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteUint(const Brx& aName, TUint aValue)
{
    Bws<Ascii::kMaxUintStringBytes> buf;
    (void)Ascii::AppendDec(buf, aValue);
    WriteVariable(aName, buf);
}

void PropertyWriter::PropertyWriteBool(const Brx& aName, TBool aValue)
{
    PropertyWriteUint(aName, (aValue? 1 : 0));
}

void PropertyWriter::PropertyWriteBinary(const Brx& aName, const Brx& aValue)
{
    WriterBwh writer(1024);
    Converter::ToBase64(writer, aValue);
    Brh buf;
    writer.TransferTo(buf);
    WriteVariable(aName, buf);
}

void PropertyWriter::WriteVariable(const Brx& aName, const Brx& aValue)
{
    ASSERT(iWriter != NULL);
    WriteVariable(*iWriter, aName, aValue);
}


// Publisher

Publisher::Publisher(const TChar* aName, Fifo<Publisher*>& aFree)
    : Thread(aName)
    , iFree(aFree)
{
}

Publisher::~Publisher()
{
    Kill();
    Join();
}

void Publisher::Publish(DviSubscription* aSubscription)
{
    iSubscription = aSubscription;
    Signal();
}

#ifdef DEFINE_TRACE
void Publisher::Error(const TChar* aErr)
#else
void Publisher::Error(const TChar* /*aErr*/)
#endif
{
    LOG2(kDvEvent, kError, "Error - %s - from SID ", aErr);
    LOG2(kDvEvent, kError, iSubscription->Sid());
    LOG2(kDvEvent, kError, "\n");
}

void Publisher::Run()
{
    for (;;) {
        Wait();
        try {
            iSubscription->WriteChanges();
        }
        catch (HttpError&) {
            Error("Http");
        }
        catch (NetworkError&) {
            Error("Network");
        }
        catch (NetworkTimeout&) {
            Error("Timeout");
        }
        catch (WriterError&) {
            Error("Writer");
        }
        catch (ReaderError&) {
            Error("Reader");
        }

        iSubscription->RemoveRef();
        iFree.Write(this);
    }
}


// DviSubscriptionManager

DviSubscriptionManager::DviSubscriptionManager()
    : Thread("DVSM")
    , iLock("DSBM")
    , iFree(Stack::InitParams().DvNumPublisherThreads())
{
    const TUint numPublisherThreads = Stack::InitParams().DvNumPublisherThreads();
    LOG(kDvEvent, "> DviSubscriptionManager: creating %u publisher threads\n", numPublisherThreads);
    TChar thName[5];
    iPublishers = (Publisher**)malloc(sizeof(*iPublishers) * numPublisherThreads);
    for (TUint i=0; i<numPublisherThreads; i++) {
        (void)sprintf(&thName[0], "DP%2lu", (unsigned long)i);
        iPublishers[i] = new Publisher(&thName[0], iFree);
        iFree.Write(iPublishers[i]);
        iPublishers[i]->Start();
    }
    Start();
}

DviSubscriptionManager::~DviSubscriptionManager()
{
    LOG(kDvEvent, "> ~DviSubscriptionManager\n");

    iLock.Wait();
    Kill();
    Join();
    iLock.Signal();

    const TUint numPublisherThreads = Stack::InitParams().DvNumPublisherThreads();
    for (TUint i=0; i<numPublisherThreads; i++) {
        delete iPublishers[i];
    }
    free(iPublishers);
    LOG(kDvEvent, "< ~DviSubscriptionManager\n");
}

void DviSubscriptionManager::AddSubscription(DviSubscription& aSubscription)
{
    DviSubscriptionManager& self = DviSubscriptionManager::Self();
    self.iLock.Wait();
    Brn sid(aSubscription.Sid());
    self.iMap.insert(std::pair<Brn,DviSubscription*>(sid, &aSubscription));
    self.iLock.Signal();
}

void DviSubscriptionManager::RemoveSubscription(DviSubscription& aSubscription)
{
    DviSubscriptionManager& self = DviSubscriptionManager::Self();
    self.iLock.Wait();
    Brn sid(aSubscription.Sid());
    Map::iterator it = self.iMap.find(sid);
    if (it != self.iMap.end()) {
        self.iMap.erase(it);
    }
    self.iLock.Signal();
}

DviSubscription* DviSubscriptionManager::Find(const Brx& aSid)
{
    DviSubscription* subs = NULL;
    DviSubscriptionManager& self = DviSubscriptionManager::Self();
    self.iLock.Wait();
    Brn sid(aSid);
    Map::iterator it = self.iMap.find(sid);
    if (it != self.iMap.end()) {
        subs = it->second;
    }
    self.iLock.Signal();
    return subs;
}

void DviSubscriptionManager::QueueUpdate(DviSubscription& aSubscription)
{
    DviSubscriptionManager& self = DviSubscriptionManager::Self();
    ASSERT(aSubscription.PropertiesInitialised());
    aSubscription.AddRef();
    self.iLock.Wait();
    self.iList.push_back(&aSubscription);
    self.Signal();
    self.iLock.Signal();
}

DviSubscriptionManager& DviSubscriptionManager::Self()
{
    return DviStack::SubscriptionManager();
}

void DviSubscriptionManager::Run()
{
    for (;;) {
        Wait();
        Publisher* publisher = iFree.Read();
        iLock.Wait();
        DviSubscription* subscription = iList.front();
        iList.pop_front();
        iLock.Signal();
        publisher->Publish(subscription);
    }
}
