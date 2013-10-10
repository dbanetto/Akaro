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
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#define INPUT_SETTINGS_FILE "input.ini"

namespace Input {

struct Key {
    SDL_Scancode scan_code;
    SDL_Keymod  keymod;
};

Key StringToKeys (std::string keys);
std::string KeysToString (Key key);

class InputHandler:
        public IO::Settings
{
/*
 * TODO: Add Mouse Support
 * TODO: Add Game Controller Support (Xbox 360 and PS3 Controller)
 * TODO: Multi-key Support
 */

public:
    InputHandler();
    virtual ~InputHandler();


    bool getKey (std::string header , std::string key , Key* keycode);
    void setKey (std::string header , std::string key , Key  value);



};

} /* namespace Input */

#endif /* INPUTHANDLER_H_ */
