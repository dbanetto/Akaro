/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include <SDL2/SDL_platform.h>

#ifndef ENV_H_
#define ENV_H_

// Check windows
#if _WIN32 || _WIN64
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

namespace etc {

void printSystemInfo();

}
#endif // Header Safety
