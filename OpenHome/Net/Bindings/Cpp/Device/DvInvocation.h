#ifndef HEADER_DVINVOCATIONSTD
#define HEADER_DVINVOCATIONSTD

#include <OpenHome/OsTypes.h>

namespace OpenHome {
namespace Net {

class IDvInvocationStd
{
public:
    virtual uint32_t Version() const = 0;
    virtual TIpAddress Adapter() const = 0;
    virtual const char* ResourceUriPrefix() const = 0;
    virtual ~IDvInvocationStd() {}
};

class IDviInvocation;
class DvInvocationStd : public IDvInvocationStd
{
public:
    DvInvocationStd(IDviInvocation& aInvocation);
private:
    uint32_t Version() const;
    TIpAddress Adapter() const;
    const char* ResourceUriPrefix() const;
private:
    DvInvocationStd(const DvInvocationStd &);
    void operator=(const DvInvocationStd &);
private:
    IDviInvocation& iInvocation;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_DVINVOCATIONSTD
