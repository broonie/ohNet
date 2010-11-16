#ifndef HEADER_DVLINNCOUKDIAGNOSTICS1
#define HEADER_DVLINNCOUKDIAGNOSTICS1

#include <ZappTypes.h>
#include <Buffer.h>
#include <Core/DvDevice.h>
#include <DvProvider.h>

namespace Zapp {

class IDviInvocation;
class PropertyInt;
class PropertyUint;
class PropertyBool;
class PropertyString;
class PropertyBinary;

/**
 * Base Device for linn.co.uk:Diagnostics:1
 */
class DvProviderLinnCoUkDiagnostics1 : public DvProvider
{
public:
    virtual ~DvProviderLinnCoUkDiagnostics1() {}
    TBool SetPropertyaStateVariable(TUint aValue);
    void GetPropertyaStateVariable(TUint& aValue);
protected:
    DvProviderLinnCoUkDiagnostics1(DvDevice& aDevice);
    void EnableActionEcho();
    void EnableActionElfFile();
    void EnableActionElfFingerprint();
    void EnableActionCrashDataStatus();
    void EnableActionCrashDataFetch();
    void EnableActionCrashDataClear();
    void EnableActionSysLog();
    void EnableActionDiagnostic();
    void EnableActionStateVariable();
    void EnableActionSetStateVariable();
    void EnableActionStateVariablePeriod();
    void EnableActionSetStateVariablePeriod();
    void EnableActionReboot();
private:
    virtual void Echo(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaIn, IInvocationResponseString& aaOut);
    virtual void ElfFile(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFile);
    virtual void ElfFingerprint(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaElfFileFingerprint);
    virtual void CrashDataStatus(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aaCrashDataStatus);
    virtual void CrashDataFetch(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaCrashData);
    virtual void CrashDataClear(IInvocationResponse& aResponse, TUint aVersion);
    virtual void SysLog(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBinary& aaSysLog);
    virtual void Diagnostic(IInvocationResponse& aResponse, TUint aVersion, const Brx& aaDiagnosticType, IInvocationResponseString& aaDiagnosticInfo);
    virtual void StateVariable(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaStateVariable);
    virtual void SetStateVariable(IInvocationResponse& aResponse, TUint aVersion, TUint aaStateVariable);
    virtual void StateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseUint& aaPeriod);
    virtual void SetStateVariablePeriod(IInvocationResponse& aResponse, TUint aVersion, TUint aaPeriod);
    virtual void Reboot(IInvocationResponse& aResponse, TUint aVersion, TUint aaDelay);
private:
    DvProviderLinnCoUkDiagnostics1();
    void DoEcho(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFile(IDviInvocation& aInvocation, TUint aVersion);
    void DoElfFingerprint(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataStatus(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataFetch(IDviInvocation& aInvocation, TUint aVersion);
    void DoCrashDataClear(IDviInvocation& aInvocation, TUint aVersion);
    void DoSysLog(IDviInvocation& aInvocation, TUint aVersion);
    void DoDiagnostic(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariable(IDviInvocation& aInvocation, TUint aVersion);
    void DoStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariablePeriod(IDviInvocation& aInvocation, TUint aVersion);
    void DoReboot(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyUint* iPropertyaStateVariable;
};

} // namespace Zapp

#endif // HEADER_DVLINNCOUKDIAGNOSTICS1

