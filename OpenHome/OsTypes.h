#ifndef HEADER_OS_TYPES
#define HEADER_OS_TYPES

#define __STDC_LIMIT_MACROS
#include <stdint.h>

/**
 * Opaque handle to an OS resource
 */
typedef void* THandle;

/**
 * IpV4 address as network order uint32
 */
typedef uint32_t TIpAddress;

/**
 * Opaque handle to a singleton, setup before other Os functions are called
 */
typedef struct OsContext OsContext;

/* Doxygen groups */
/**
 * @defgroup Core          Core Services
 * @defgroup ControlPoint  Control Point Stack
 * @defgroup Device        Device Stack
 */
/**
 * @defgroup Callbacks     Callbacks
 * @ingroup  Core
 */
/**
 * @defgroup Proxies       Service Proxies
 * @ingroup ControlPoint
 */
/**
 * @defgroup Providers     Service Providers
 * @ingroup Device
 */

#endif // HEADER_OS_TYPES
