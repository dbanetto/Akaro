/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include "GameWindow.h"
#include "io/Settings.h"
#include <iostream>
#include <string>
#include "io/file.h"

int main (int argc, char* argv[]) 
{
    IO::Settings setting = IO::Settings( IO::SETTING_LOAD_ON_REQUEST );
    
    if (IO::fileExists ( SETTINGS_PATH ) == false ) {
        std::cout << "Error: Program can not start. " << SETTINGS_PATH << " cannot be found." << std::endl;
        return -1;
    }
    
    setting.load ( SETTINGS_PATH , IO::SETTINGS_DUPLICATES_INGORED );

    if (setting.exists ( "render.screen" , "width" ) == false) {
        std::cout << "Error: Program can not start. \'width\' in the section \'render.screen\' is not defined in " << SETTINGS_PATH << std::endl;
        return -2;
    }

    if (setting.exists ( "render.screen" , "height" ) == false) {
        std::cout << "Error: Program can not start. \'height\' in the section \'render.screen\' is not defined in " << SETTINGS_PATH << std::endl;
        return -3;
    }

    GameWindow gm;
    //Background Colour
    SDL_Color bg;
    bg.r = 0; bg.g = 0; bg.b = 0; 

    //Make sure the window init'ed properly
    if ( gm.Init ( "Akaro" , setting.getInt( "render.screen" , "width" ) , setting.getInt( "render.screen" , "height" ) , bg, SDL_WINDOW_OPENGL ) == 0 )
    {
        setting.clear();
        //14 - Start the game already!
        gm.Start();
    }
    return 0;
}
