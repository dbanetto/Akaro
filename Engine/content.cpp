#include "content.h"

#include "etc/Timer.h"
#include "etc/env.h"
#include "io/file.h"
#include "GameWindow.h"
#include "etc/string.h"
#include "etc/colour.h"
#include "input/KBProvider.h"
#include "input/PS3Provider.h"

#include <string>
#include <stdlib.h>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <ctime>

Content::Content()
{
	//ctor
	this->settings = IO::Settings(IO::SETTING_LOAD_ON_REQUEST);
}

Content::~Content()
{

}

int Content::load()
{
	if (IO::fileExists( SETTINGS_PATH ) == false)
	{
		std::cout << "Could not initialize due to the settings file "
				  << SETTINGS_PATH << " does not exist." ;
		return 1;
	}

	if (IO::fileExists( INPUT_SETTINGS_FILE ) == false)
	{
		std::cout << "Could not initialize due to the settings file "
				  << INPUT_SETTINGS_FILE << " does not exist." ;
		return 2;
	}

	settings.load( SETTINGS_PATH , IO::SETTINGS_DUPLICATES_INGORED );
	std::cout << SETTINGS_PATH << " loaded." << std::endl;
	//Start SDL and Others

	//Start SDL
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 3;
	}

	//Start SDL_image
	if ( IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) == 0)
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 4;
	}

	//Start SDL_mixer
	if ( Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG) == 0)
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 5;
	}

	//Start SDL_ttf
	if ( TTF_Init() == -1)
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 6;
	}

	std::cout << "All sub systems loaded." << std::endl;

	//INPUT
	input.load( INPUT_SETTINGS_FILE , IO::SETTINGS_DUPLICATES_INGORED , IO::SETTING_LOAD_ON_REQUEST);
	if (input.add_provider("kb" , new input::KBProvider() ) == false )
	{
		std::cout << "Failed to load Keyboard" << std::endl;
		return 7;
	}

	if (settings.exists("Controller" , "ps3.enable"))
	{
		bool enable = false;
		settings.getBool( "Controller" , "ps3.enable" , &enable );
		if (enable)
		{
			if (this->input.add_provider("ps3" , new input::PS3Provider() ) == false)
			{
				std::cout << "Failed to load Controller" << std::endl;
				return 7;
			}
		}
	}

	std::cout << "Input loaded" << std::endl;

	//audio.load_settings( &(this->settings) );

	return 0;
}

void Content::unload()
{
    this->audio.unloadall();
    this->gamestate.unload();
    this->input.unload();
    this->settings.unload();

    //Shutdown inited services in reverse order of init
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
/**
 * @brief Returns a pointer to the Window Settings
 */
IO::Settings* Content::Settings ()
{
	return &(this->settings);
}

input::InputManager * Content::Input()
{
	return &(this->input);
}
audio::AudioManager* Content::Audio()
{
	return &(this->audio);
}
GameStateManager* Content::Gamestate()
{
	return &(this->gamestate);
}
