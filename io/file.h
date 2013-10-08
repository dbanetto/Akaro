/*
    Author : David Barnett
    Date   : 04-10-2013
    License: MIT License
*/
#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <string>

// TODO : Add some SDL file operations

namespace IO {
    bool fileExists(const std::string& filename);
};

#endif
