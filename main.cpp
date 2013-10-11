/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include "GameWindow.h"
#include <iostream>
#include <string>
#include "io/file.h"

int main (int argc, char* argv[]) 
{

    GameWindow gm;
    //Background Colour
    SDL_Color bg;
    bg.r = 0; bg.g = 0; bg.b = 0; 

    //Make sure the window init'ed properly
    if ( gm.init ( "Akaro" , bg, SDL_WINDOW_OPENGL ) == 0 )
    {
        //14 - Start the game already!
        gm.start();
    }
    return 0;
}
