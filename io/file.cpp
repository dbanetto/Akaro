/*
    Author : David Barnett
    Date   : 04-10-2013
    License: MIT License
*/

#include "file.h"

#include <sys/stat.h>

using namespace IO;

bool IO::fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}