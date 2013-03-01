#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/TestFramework.h>
#include <OpenHome/Net/Core/OhNet.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Net;

extern void TestCpDeviceDv(CpStack& aCpStack, DvStack& aDvStack);

void OpenHome::TestFramework::Runner::Main(TInt /*aArgc*/, TChar* /*aArgv*/[], Net::InitialisationParams* aInitParams)
{
    aInitParams->SetUseLoopbackNetworkAdapter();
    Library* lib = new Library(aInitParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = NULL;
    DvStack* dvStack = NULL;
    lib->StartCombined(subnet, cpStack, dvStack);

    TestCpDeviceDv(*cpStack, *dvStack);

    delete lib;
}
