#include <OpenHome/Net/Core/DvProvider.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/DviDevice.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Net/Private/DviStack.h>

using namespace OpenHome;
using namespace OpenHome::Net;

void DvProvider::PropertiesLock()
{
    iService->PropertiesLock();
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    iDelayPropertyUpdates = true;
    lock.Signal();
}

void DvProvider::PropertiesUnlock()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    TBool report = iPropertyChanged;
    iPropertyChanged = false;
    iDelayPropertyUpdates = false;
    lock.Signal();
    iService->PropertiesUnlock();
    if (report) {
        iService->PublishPropertyUpdates();
    }
}

DvProvider::DvProvider(DviDevice& aDevice, const TChar* aDomain, const TChar* aType, TUint aVersion)
    : iDvStack(aDevice.GetDvStack())
    , iDelayPropertyUpdates(false)
    , iPropertyChanged(false)
{
    iService = new DviService(iDvStack, aDomain, aType, aVersion);
    aDevice.AddService(iService);
}

DvProvider::~DvProvider()
{
    iService->Disable();
    iService->RemoveRef();
}

bool DvProvider::SetPropertyInt(PropertyInt& aProperty, TInt aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyUint(PropertyUint& aProperty, TUint aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBool(PropertyBool& aProperty, TBool aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyString(PropertyString& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

bool DvProvider::SetPropertyBinary(PropertyBinary& aProperty, const Brx& aValue)
{
    if (aProperty.SetValue(aValue)) {
        TryPublishUpdate();
        return true;
    }
    return false;
}

void DvProvider::TryPublishUpdate()
{
    Mutex& lock = iDvStack.Env().Mutex();
    lock.Wait();
    TBool publish = !iDelayPropertyUpdates;
    if (iDelayPropertyUpdates) {
        iPropertyChanged = true;
    }
    lock.Signal();
    if (publish) {
        iService->PublishPropertyUpdates();
    }
}    
