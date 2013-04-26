#ifndef HEADER_MDNSPROVIDER
#define HEADER_MDNSPROVIDER

#include <OpenHome/Net/Private/Bonjour.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Private/MdnsPlatform.h>

namespace OpenHome {

class Environment;

namespace Net {

class MdnsProvider : public IMdnsProvider
{
public:
    MdnsProvider(Environment& aStack, const TChar* aHost);
    virtual ~MdnsProvider();
    virtual void MdnsSetHostName(const TChar* aName);
    virtual TUint MdnsCreateService();
    virtual void MdnsDestroyService(TUint aHandle);
    virtual void MdnsAppendTxtRecord(TChar* aBuffer, TUint aLength, const TChar* aKey, const TChar* aValue);
    virtual void MdnsRegisterService(TUint aHandle, const TChar* aName, const TChar* aType, TIpAddress aInterface, TUint aPort, const TChar* aInfo);
    virtual void MdnsDeregisterService(TUint aHandle);
private:
    MdnsPlatform iPlatform;
};
    
} // namespace Net
} // namespace OpenHome

#endif // HEADER_MDNSPROVIDER
