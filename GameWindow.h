/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#pragma once

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

//Cross-Platform
#if __GNUC__
#include "SDL2\SDL.h"
#include "SDL2\SDL_ttf.h"
#include "SDL2\SDL_net.h"
#include "SDL2\SDL_mixer.h"
#include "SDL2\SDL_image.h"
#else
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_net.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#endif

#include "ui/Label.h"
#include "io/Settings.h"
#include "input/InputHandler.h"

//TODO : Support Multiple 'Game States'

/// <summary>
/// GameWindow Class to handle Rendering, Updating and events
/// </summary>
class GameWindow
{
public:
    GameWindow();
    virtual ~GameWindow();

    int Init(const char* TITLE , SDL_Color BACKGROUND_COLOUR ,  int SDL_SCREEN_FLAGS );

    void Start(void);
protected:
    void Render(double delta);
    void Update(double delta);
    void Event (SDL_Event e , double delta);

    void Load();
    void Unload();
private:
    
    //Private variables
    SDL_Renderer* renderer;
    SDL_Window*   window;
    bool inited, quit;

    //View port
    //Camera camera;

    int CURRENT_FPS;
    double GAMETIME_MULTIPLIER;
    
    //background colour
    SDL_Color background;

    //Settings
    IO::Settings settings;
    Input::InputHandler input;

    TTF_Font* font;
    ui::Label lb;
};

#endif
