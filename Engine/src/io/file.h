/*
    Author : David Barnett
    Date   : 04-10-2013
    License: MIT License
*/
#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include "../etc/env.h"
// TODO : Add SDL file operations wrappers

#if __GNUC__
#include <SDL2/SDL_filesystem.h>
#else
#include "SDL_filesystem.h"
#endif


#ifdef __WINDOWS__
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

namespace IO
{
	bool fileExists(const std::string& filename);
};

#endif
