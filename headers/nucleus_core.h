#ifndef PLATFORM_ABSTRACT_CORE_H
#define PLATFORM_ABSTRACT_CORE_H
#ifdef __cplusplus
extern "C" {
#endif
#include "objc_mac_gui.h"
// types
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long      ul64;
typedef unsigned long long u64;

typedef signed char        i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long long   i64;

typedef u64 Nucleus_size_t;
typedef i64 Nucleus_ssize_t;
typedef u8  Nucleus_BOOL;

#define Nucleus_TRUE 1
#define Nucleus_FALSE 0

typedef struct Nucleus_FRect {
    float x;
    float y;
    float w;
    float h;
} Nucleus_FRect;

// platform abstraction
#if defined(__x86_64__)
    // void x86_64_print(const char* s);
    // #define print x86_64_print
#elif defined(__arm64__)

    #if defined(__APPLE__)
        void apple_arm64_log_msg(const char* cstr);
        void apple_arm64_sleep(const NSTimeInterval interval);
        void apple_arm64_init_window(const Nucleus_FRect* rect);
        #define Nucleus_log apple_arm64_log_msg
        #define Nucleus_sleepSeconds apple_arm64_sleep
        #define Nucleus_initWindow apple_arm64_init_window
    #else
        // abstract arm64
#endif

#else
#error "Unsupported architecture"
#endif //PLATFORM_UTILS_H

#ifdef __cplusplus
}
#endif

#endif //PLATFORM_ABSTRACT_CORE_H
