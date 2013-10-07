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

InputHandler::InputHandler() {
	// TODO Auto-generated constructor stub

}

InputHandler::~InputHandler() {
	// TODO Auto-generated destructor stub
}



bool getScanCode (std::string header , std::string  key , Key* sacncode)
{
	//All keys to be in a *.keys
	key = key + ".keys";

	return false;
}

void setKeyCode (std::string header , std::string key , Key  value)
{
	key = key + ".keys";

}

Key StringToKeys (std::string keys)
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
std::string KeysToString (Key key)
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

