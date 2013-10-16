/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include "GameWindow.h"
#include "etc/colour.h"

int main (int argc, char* argv[]) 
{
    GameWindow gm;

    //Make sure the window init'ed properly
    if ( gm.init ( "Akaro" , etc::toColour(etc::COLOUR_BLACK) , SDL_WINDOW_OPENGL ) == 0 )
    {
        //14 - Start the game already!
        gm.start();
    }
    return 0;
}
