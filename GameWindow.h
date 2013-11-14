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
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_net.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#endif

#include "ui/Label.h"
#include "ui/Button.h"
#include "io/Settings.h"
#include "input/InputHandler.h"
#include "etc/battery.h"
#include "states/GameStateManager.h"
#include "audio/AudioManager.h"
#include "graphics/TextureManager.h"

//TODO : Support Multiple 'Game States'

/// <summary>
/// GameWindow Class to handle Rendering, Updating and events
/// </summary>
class GameWindow
{
public:
    GameWindow();
    virtual ~GameWindow();

    int init(const char* TITLE , SDL_Color BACKGROUND_COLOUR ,  int SDL_SCREEN_FLAGS );

    void start(void);
    int CURRENT_FPS;

    //Get Settings and Content Managers
    IO::Settings* getSettings();
    Input::InputHandler * getInputHandler();
    audio::AudioManager* getAudio();
    graphics::TextureManager* getTextures();

protected:
    void render(const double& delta);
    void update(const double& delta);
    void event (SDL_Event e , const double& delta);

    void load();
    void unload();

    //util functions
    void screenshot();
private:
    GameStateManager gamestate;
    
    //Private variables
    SDL_Renderer* renderer;
    SDL_Window*   window;
    bool inited, quit;

    //View port
    //Camera camera;


    double GAMETIME_MULTIPLIER;
    
    //background colour
    SDL_Color background;

    //Settings and Content managers
    IO::Settings settings;
    Input::InputHandler input;
    audio::AudioManager audio;
    graphics::TextureManager textures;


    //Battery
    bool has_battery;
    //Measured in seconds
    double last_battery_check;
};

#endif
