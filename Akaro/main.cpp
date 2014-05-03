/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include "AkaroWindow.h"
#include "Engine/etc/colour.h"
#include "Engine/content.h"
#include "Engine/etc/env.h"

#include <iostream>
#include <string>

#if __GNUC__
#include <SDL2/SDL_version.h>
#else
#include "SDL_version.h"
#endif

int main ( int argc, char* argv[] )
{
	{
		SDL_version running;
		SDL_GetVersion( &running );
		SDL_version linked;
		SDL_VERSION( &linked );

		if ( running.patch < linked.patch && running.minor < linked.minor )
		{
			std::cout << "You are running an out of date version of SDL2" << std::endl;
			std::cout << "You can the new version from http://libsdl.org" << std::endl;
		}
	}

	Content content;
	//Load base content
	content.init();

	if (content.Settings()->exists("info" , "printinfo"))
	{
		bool print = false;
		if ( content.Settings()->getBool("info" , "printinfo" , &print ) )
		{
			if (print)
			{
				etc::printSystemInfo();
			}
		} else {
			std::string option;
			content.Settings()->get("info" , "printinfo" , &option);
			std::cout << option << std::endl;
			if (option == "full")
			{
				etc::printSystemInfo(true);
			}
		}
	}

	AkaroWindow gm = AkaroWindow ( &content );

	//Make sure the window init'ed properly
	if ( gm.init ( "Akaro" , etc::toColour( 4, 107, 19 , 100 ) , SDL_WINDOW_OPENGL ) == 0 )
	{
		//14 - Start the game already!
		gm.start();

	}
	content.unload();
	return 0;
}
