#pragma once
#include "../io/settings.h"

#if __GNUC__
#include "SDL2\SDL.h"
#else
#include "SDL.h"
#endif

namespace Input {

    class InputSettings :
        public IO::Settings
    {
    public:
        InputSettings(void);
        ~InputSettings(void);

        SDL_Scancode getScanCode (std::string header , std::string  key);
        SDL_Keycode  getKeyCode (std::string header , std::string  key);

        void setScanCode (std::string header , std::string key , SDL_Scancode  value);
        void setKeyCode (std::string header , std::string key , SDL_Keycode  value);
    };
}
