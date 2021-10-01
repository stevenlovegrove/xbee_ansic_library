/**
    @defgroup hal_arduino HAL: Arduino (platformIO)
    Arduino platform 
*/


#ifndef __XBEE_PLATFORM_ARDUINO
#define __XBEE_PLATFORM_ARDUINO

    #ifndef LITTLE_ENDIAN
    #  define LITTLE_ENDIAN 1234
    #endif
    #ifndef BYTE_ORDER
    #  define BYTE_ORDER LITTLE_ENDIAN
    #endif


    #define strcmpi         strcasecmp
    #define strncmpi        strncasecmp

    // Load platform's endian header to learn whether we're big or little.
    #include <sys/types.h>

    // macros used to declare a packed structure (no alignment of elements)
    // The more-flexible XBEE_PACKED() replaced PACKED_STRUCT in 2019.
    #define PACKED_STRUCT       struct __attribute__ ((__packed__))
    #define XBEE_PACKED(name, decl) PACKED_STRUCT name decl

    #define _f_memcpy       memcpy
    #define _f_memset       memset

    // stdint.h for int8_t, uint8_t, int16_t, etc. types
    #include <stdint.h>

    typedef int bool_t;

    // inttypes.h for PRIx16, PRIx32, etc. macros
    #include <inttypes.h>

    #ifdef __cplusplus
        // forward declaration
        namespace arduino{ class Stream; }
    #endif

    typedef struct xbee_serial_t {
        uint32_t baudrate;
#ifdef __cplusplus
        arduino::Stream* device;
#else
        void* device;
#endif
    } xbee_serial_t;

    // Unix epoch is 1/1/1970
    #define ZCL_TIME_EPOCH_DELTA    ZCL_TIME_EPOCH_DELTA_1970

    #define XBEE_MS_TIMER_RESOLUTION 10

#endif      // __XBEE_PLATFORM_ARDUINO
