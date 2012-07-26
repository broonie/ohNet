#ifndef HEADER_NETWORKINTERFACELIST
#define HEADER_NETWORKINTERFACELIST

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Functor.h>
#include <OpenHome/FunctorNetworkAdapter.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>
#include <map>

namespace OpenHome {

class NetworkAdapterList : private IStackObject
{
public:
    static const TUint kListenerIdNull = 0;
public:
    NetworkAdapterList(TIpAddress aDefaultSubnet=0);
    ~NetworkAdapterList();
    NetworkAdapter* CurrentAdapter(const char* aCookie) const;
    const std::vector<NetworkAdapter*>& List() const;
    std::vector<NetworkAdapter*>* CreateSubnetList() const;
    static void DestroySubnetList(std::vector<NetworkAdapter*>* aList);
    void SetCurrentSubnet(TIpAddress aSubnet);
    TUint AddCurrentChangeListener(Functor aFunctor);
    void RemoveCurrentChangeListener(TUint aId);
    TUint AddSubnetListChangeListener(Functor aFunctor);
    void RemoveSubnetListChangeListener(TUint aId);
    TUint AddSubnetAddedListener(FunctorNetworkAdapter aFunctor);
    void RemoveSubnetAddedListener(TUint aId);
    TUint AddSubnetRemovedListener(FunctorNetworkAdapter aFunctor);
    void RemoveSubnetRemovedListener(TUint aId);
    TUint AddNetworkAdapterChangeListener(FunctorNetworkAdapter aFunctor);
    void RemoveNetworkAdapterChangeListener(TUint aId);
private:
    typedef std::map<TUint,Functor> Map;
    typedef std::map<TUint,FunctorNetworkAdapter> MapNetworkAdapter;
    std::vector<NetworkAdapter*>* CreateSubnetListLocked() const;
    TUint AddListener(Functor aFunctor, Map& aMap);
    void RemoveSubnetListChangeListener(TUint aId, Map& aMap);
    TUint AddSubnetListener(FunctorNetworkAdapter aFunctor, MapNetworkAdapter& aMap);
    void RemoveSubnetListener(TUint aId, MapNetworkAdapter& aMap);
    static void InterfaceListChanged(void* aPtr);
    static TInt FindSubnet(TIpAddress aSubnet, const std::vector<NetworkAdapter*>& aList);
    void UpdateCurrentAdapter();
    void HandleInterfaceListChanged();
    void RunCallbacks(Map& aMap);
    void DoRunCallbacks(Map& aMap);
    void RunSubnetCallbacks(MapNetworkAdapter& aMap, NetworkAdapter& aAdapter);
    static TBool CompareSubnets(NetworkAdapter* aI, NetworkAdapter* aJ);
    /**
     * Some platforms behave poorly for a short period after delivering a subnet change message.
     * e.g. Windows reports adapters as available/usable but attempts to bind to them may fail.
     * This function helps work around that by calling a client-specified function, catching and
     * NetworkError failure then re-trying shortly later.  It eventually gives up if errors continue.
     *
     * Frequency and overall duration of retries could be user-configurable but are currently hard-coded.
     */
//     static void TempFailureRetry(Functor& aCallback);
private: // from IStackObject
    void ListObjectDetails() const;
private:
    mutable Mutex iListLock;
    Mutex iListenerLock;
    std::vector<NetworkAdapter*>* iNetworkAdapters;
    std::vector<NetworkAdapter*>* iSubnets;
    mutable NetworkAdapter* iCurrent;
    TIpAddress iDefaultSubnet;
    Map iListenersCurrent;
    Map iListenersSubnet;
    MapNetworkAdapter iListenersAdded;
    MapNetworkAdapter iListenersRemoved;
    MapNetworkAdapter iListenersAdapterChanged;
    TUint iNextListenerId;
};

} // namespace OpenHome

#endif // HEADER_NETWORKINTERFACELIST
