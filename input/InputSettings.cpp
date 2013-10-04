#include "InputSettings.h"

using namespace Input;

InputSettings::InputSettings(void)
    : IO::Settings ( IO::SETTING_LOAD_ON_REQUEST )
{

}


InputSettings::~InputSettings(void)
{

}

SDL_Scancode InputSettings::getScanCode (std::string header , std::string  key) 
{
    return SDL_GetScancodeFromName ( this->get(header , key ).c_str() );
}
SDL_Keycode  InputSettings::getKeyCode (std::string header , std::string  key)
{
    return SDL_GetKeyFromName ( this->get(header , key ).c_str() );
}

void InputSettings::setScanCode (std::string header , std::string key , SDL_Scancode  value)
{
    this->set ( header , key , SDL_GetScancodeName( value ) );
}

void InputSettings::setKeyCode (std::string header , std::string key , SDL_Keycode  value)
{
    this->set ( header , key , SDL_GetKeyName( value ) );
}