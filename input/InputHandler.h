/*
 * InputHandler.h
 *
 *  Created on: 6/10/2013
 *      Author: drb
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "../io/settings.h"

#if __GNUC__
#include "SDL2\SDL.h"
#else
#include "SDL.h"
#endif

namespace Input {

struct Keys {
	std::vector<SDL_Scancode> key_codes;
	SDL_Keymod  keymod;
};

class InputHandler:
        public IO::Settings
{
public:
	InputHandler();
	virtual ~InputHandler();

	SDL_Scancode getScanCode (std::string header , std::string  key);
	SDL_Keycode  getKeyCode (std::string header , std::string  key);

	void setScanCode (std::string header , std::string key , SDL_Scancode  value);
	void setKeyCode (std::string header , std::string key , SDL_Keycode  value);

};

} /* namespace Input */

#endif /* INPUTHANDLER_H_ */
