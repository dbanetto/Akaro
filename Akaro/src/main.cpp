/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include "GameWindow.h"
#include "etc/colour.h"
#include "content.h"

#include <iostream>
#if __GNUC__
#include <SDL2/SDL_version.h>
#else
#include "SDL_version.h"
#endif

int main (int argc, char* argv[])
{
	{
		SDL_version running;
		SDL_GetVersion(&running);
		SDL_version linked;
		SDL_VERSION(&linked);

		if (running.patch < linked.patch && running.minor < linked.minor)
		{
			std::cout << "You are running an out of date version of SDL2" << std::endl;
			std::cout << "You can the new version from http://libsdl.org" << std::endl;
		}
	}

	Content content;
	//Load base content
	content.load();

	GameWindow gm = GameWindow (&content);

	//Make sure the window init'ed properly
	if ( gm.init ( "Akaro" , etc::toColour(4,107,19 , 100) , SDL_WINDOW_OPENGL ) == 0 )
	{
		//14 - Start the game already!
		gm.start();

	}
	content.unload();
	return 0;
}
