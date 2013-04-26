#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/OhNetTypes.h>

using namespace OpenHome;
using namespace OpenHome::Net;

MdnsProvider::MdnsProvider(Environment& aStack, const TChar* aHost)
    : iPlatform(aStack, aHost)
{
}

MdnsProvider::~MdnsProvider()
{
}

void MdnsProvider::MdnsSetHostName(const TChar* aName)
{
    iPlatform.SetHostName(aName);
}

TUint MdnsProvider::MdnsCreateService()
{
    return iPlatform.CreateService();
}

void MdnsProvider::MdnsDestroyService(TUint aHandle)
{
    iPlatform.DeregisterService(aHandle);
}

void MdnsProvider::MdnsAppendTxtRecord(TChar* aBuffer, TUint aLength, const TChar* aKey, const TChar* aValue)
{
    iPlatform.AppendTxtRecord(aBuffer, aLength, aKey, aValue);
}

void MdnsProvider::MdnsRegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo)
{
    iPlatform.RegisterService(aHandle, aName, aType, aInterface, aPort, aInfo);
}

void MdnsProvider::MdnsDeregisterService(TUint aHandle)
{
    iPlatform.DeregisterService(aHandle);
}
