/*
 * KBProvider.h
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#ifndef KBPROVIDER_H_
#define KBPROVIDER_H_

#include "InputProvider.h"

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <string>
#include <vector>

struct Key {
    std::vector<SDL_Scancode> scan_codes;
    SDL_Keymod  keymod;
};

Key stringToKeys (std::string keys);
std::string keysToString (Key key);

namespace input
{

    class KBProvider : public input::InputProvider
    {
        public:
            KBProvider ();
            virtual ~KBProvider ();

            void load   ();
            void unload ();
    };

} /* namespace input */

#endif /* KBPROVIDER_H_ */
