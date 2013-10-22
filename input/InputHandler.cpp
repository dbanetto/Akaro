/*
 * InputHandler.cpp
 *
 *  Created on: 6/10/2013
 *      Author: drb
 */

#include "InputHandler.h"
#include "../etc/string.h"

#include <stdlib.h>
#include <string>
#include <iostream>

namespace Input {

InputHandler::InputHandler() : Settings(IO::SETTING_LOAD_ON_REQUEST) {
  this->controller = nullptr;
}

InputHandler::~InputHandler() {

}


/**
 *
 * @param header of INI section.
 * @note  root is empty string
 * @param key name of the variable to accessed
 * @param out a pointer to be written to
 * @return True on success
 */
bool InputHandler::getKey (std::string header , std::string  key , Key* out)
{
    //All keys to be in a *.keys
    key = key + ".key";
    std::string outp;
    bool result = this->get( header , key , &outp );
    if (result) {
        *out = stringToKeys( outp );
        return true;
    } else {
        return false;
    }
}

void InputHandler::setKey (std::string header , std::string key , Key  value)
{
    key = key + ".key";
    this->set( header , key , keysToString(value) );
}

Key stringToKeys (std::string keys)
{
    Key out;
    std::string key = keys.substr( 0 , keys.find( "+" ) );
    std::string kmod;
    if ( keys.find( "+" ) != keys.npos ) {
        kmod = keys.substr( keys.find( "+" ) + 1 ,  keys.length() - keys.find( "+" ) );
    }

    if (kmod != "") {
        out.scan_code = SDL_GetScancodeFromName( key.c_str() );
        out.keymod = (SDL_Keymod)( atoi ( kmod.c_str() ));
    } else {
        out.scan_code = SDL_GetScancodeFromName( key.c_str() );
        out.keymod = KMOD_NONE;
    }


    return out;
}
std::string keysToString (Key key)
{
    std::string out;

    out += std::string(SDL_GetScancodeName(key.scan_code));

    if ((int)(key.keymod) != 0)
    {
        out += "+";
        out += etc::convInt(key.keymod);
    }

    return out;
}

} /* namespace Input */

