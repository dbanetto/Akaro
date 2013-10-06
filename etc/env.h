/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#ifndef ENV_H_
#define ENV_H_

// Check windows
#if _WIN32 || _WIN64
#define __WINDOWS__
    #if _WIN64
        #define ENV64
    #else
        #define ENV32
    #endif
#endif

// Check GCC
#if __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENV64
    #else
        #define ENV32
    #endif
#endif

//Check if Linux
#if __linux
    #define __LINUX__
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define __MACOSX__
    #endif
#endif

namespace etc {

void printSystemInfo();

}
#endif // Header Safety
