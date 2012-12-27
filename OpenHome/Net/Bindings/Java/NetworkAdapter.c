#include <jni.h>
#include <stdlib.h>
#include "NetworkAdapter.h"
#include "OpenHome/Net/C/OhNet.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_openhome_net_core_NetworkAdapter
 * Method:    OhNetNetworkAdapterAddress
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_NetworkAdapter_OhNetNetworkAdapterAddress
  (JNIEnv *aEnv, jclass aClass, jlong aNif)
{
	TIpAddress ipAddr;
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)aNif;
	aEnv = aEnv;
	aClass = aClass;

	ipAddr = OhNetNetworkAdapterAddress(adapter);
	
	return (jint) ipAddr;
}

/*
 * Class:     org_openhome_net_core_NetworkAdapter
 * Method:    OhNetNetworkAdapterSubnet
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_NetworkAdapter_OhNetNetworkAdapterSubnet
  (JNIEnv *aEnv, jclass aClass, jlong aNif)
{
	TIpAddress ipAddr;
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)aNif;
	aEnv = aEnv;
	aClass = aClass;

	ipAddr = OhNetNetworkAdapterSubnet(adapter);
	
	return (jint) ipAddr;
}

/*
 * Class:     org_openhome_net_core_NetworkAdapter
 * Method:    OhNetNetworkAdapterMask
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_NetworkAdapter_OhNetNetworkAdapterMask
  (JNIEnv *aEnv, jclass aClass, jlong aNif)
{
	TIpAddress ipAddr;
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)aNif;
	aEnv = aEnv;
	aClass = aClass;

	ipAddr = OhNetNetworkAdapterMask(adapter);
	
	return (jint) ipAddr;
}

/*
 * Class:     org_openhome_net_core_NetworkAdapter
 * Method:    OhNetNetworkAdapterName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_core_NetworkAdapter_OhNetNetworkAdapterName
  (JNIEnv *aEnv, jclass aClass, jlong aNif)
{
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)aNif;
	const char* name = OhNetNetworkAdapterName(adapter);
	aClass = aClass;
	
	return ((*aEnv)->NewStringUTF(aEnv, name));
}

/*
 * Class:     org_openhome_net_core_NetworkAdapter
 * Method:    OhNetNetworkAdapterFullName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_core_NetworkAdapter_OhNetNetworkAdapterFullName
  (JNIEnv *aEnv, jclass aClass, jlong aNif)
{
	OhNetHandleNetworkAdapter adapter = (OhNetHandleNetworkAdapter) (size_t)aNif;
	char* name = OhNetNetworkAdapterFullName(adapter);
    jstring jname;
	aClass = aClass;

	jname = ((*aEnv)->NewStringUTF(aEnv, name));
    free(name);
    return jname;
}

#ifdef __cplusplus
}
#endif
