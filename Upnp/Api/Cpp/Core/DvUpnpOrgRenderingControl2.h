#ifndef HEADER_DVUPNPORGRENDERINGCONTROL2
#define HEADER_DVUPNPORGRENDERINGCONTROL2

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
 * Base Device for upnp.org:RenderingControl:2
 */
class DvProviderUpnpOrgRenderingControl2 : public DvProvider
{
public:
    virtual ~DvProviderUpnpOrgRenderingControl2() {}
    TBool SetPropertyLastChange(const Brx& aValue);
    void GetPropertyLastChange(Brhz& aValue);
protected:
    DvProviderUpnpOrgRenderingControl2(DvDevice& aDevice);
    void EnableActionListPresets();
    void EnableActionSelectPreset();
    void EnableActionGetBrightness();
    void EnableActionSetBrightness();
    void EnableActionGetContrast();
    void EnableActionSetContrast();
    void EnableActionGetSharpness();
    void EnableActionSetSharpness();
    void EnableActionGetRedVideoGain();
    void EnableActionSetRedVideoGain();
    void EnableActionGetGreenVideoGain();
    void EnableActionSetGreenVideoGain();
    void EnableActionGetBlueVideoGain();
    void EnableActionSetBlueVideoGain();
    void EnableActionGetRedVideoBlackLevel();
    void EnableActionSetRedVideoBlackLevel();
    void EnableActionGetGreenVideoBlackLevel();
    void EnableActionSetGreenVideoBlackLevel();
    void EnableActionGetBlueVideoBlackLevel();
    void EnableActionSetBlueVideoBlackLevel();
    void EnableActionGetColorTemperature();
    void EnableActionSetColorTemperature();
    void EnableActionGetHorizontalKeystone();
    void EnableActionSetHorizontalKeystone();
    void EnableActionGetVerticalKeystone();
    void EnableActionSetVerticalKeystone();
    void EnableActionGetMute();
    void EnableActionSetMute();
    void EnableActionGetVolume();
    void EnableActionSetVolume();
    void EnableActionGetVolumeDB();
    void EnableActionSetVolumeDB();
    void EnableActionGetVolumeDBRange();
    void EnableActionGetLoudness();
    void EnableActionSetLoudness();
    void EnableActionGetStateVariables();
    void EnableActionSetStateVariables();
private:
    virtual void ListPresets(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseString& aCurrentPresetNameList);
    virtual void SelectPreset(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aPresetName);
    virtual void GetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBrightness);
    virtual void SetBrightness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBrightness);
    virtual void GetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentContrast);
    virtual void SetContrast(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredContrast);
    virtual void GetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentSharpness);
    virtual void SetSharpness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredSharpness);
    virtual void GetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoGain);
    virtual void SetRedVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoGain);
    virtual void GetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoGain);
    virtual void SetGreenVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoGain);
    virtual void GetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoGain);
    virtual void SetBlueVideoGain(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoGain);
    virtual void GetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentRedVideoBlackLevel);
    virtual void SetRedVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredRedVideoBlackLevel);
    virtual void GetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentGreenVideoBlackLevel);
    virtual void SetGreenVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredGreenVideoBlackLevel);
    virtual void GetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentBlueVideoBlackLevel);
    virtual void SetBlueVideoBlackLevel(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredBlueVideoBlackLevel);
    virtual void GetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseUint& aCurrentColorTemperature);
    virtual void SetColorTemperature(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TUint aDesiredColorTemperature);
    virtual void GetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentHorizontalKeystone);
    virtual void SetHorizontalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredHorizontalKeystone);
    virtual void GetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, IInvocationResponseInt& aCurrentVerticalKeystone);
    virtual void SetVerticalKeystone(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, TInt aDesiredVerticalKeystone);
    virtual void GetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentMute);
    virtual void SetMute(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredMute);
    virtual void GetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseUint& aCurrentVolume);
    virtual void SetVolume(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TUint aDesiredVolume);
    virtual void GetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aCurrentVolume);
    virtual void SetVolumeDB(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TInt aDesiredVolume);
    virtual void GetVolumeDBRange(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseInt& aMinValue, IInvocationResponseInt& aMaxValue);
    virtual void GetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, IInvocationResponseBool& aCurrentLoudness);
    virtual void SetLoudness(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aChannel, TBool aDesiredLoudness);
    virtual void GetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aStateVariableList, IInvocationResponseString& aStateVariableValuePairs);
    virtual void SetStateVariables(IInvocationResponse& aResponse, TUint aVersion, TUint aInstanceID, const Brx& aRenderingControlUDN, const Brx& aServiceType, const Brx& aServiceId, const Brx& aStateVariableValuePairs, IInvocationResponseString& aStateVariableList);
private:
    DvProviderUpnpOrgRenderingControl2();
    void DoListPresets(IDviInvocation& aInvocation, TUint aVersion);
    void DoSelectPreset(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBrightness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetContrast(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetContrast(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetSharpness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetSharpness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoGain(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetRedVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetGreenVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetBlueVideoBlackLevel(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetColorTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetColorTemperature(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetHorizontalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVerticalKeystone(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetMute(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolume(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDB(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetVolumeDB(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetVolumeDBRange(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetLoudness(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetLoudness(IDviInvocation& aInvocation, TUint aVersion);
    void DoGetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
    void DoSetStateVariables(IDviInvocation& aInvocation, TUint aVersion);
private:
    PropertyString* iPropertyLastChange;
};

} // namespace Zapp

#endif // HEADER_DVUPNPORGRENDERINGCONTROL2

