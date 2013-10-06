/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include <iostream>
#include "etc/Timer.h"
#include <string>
#include <sstream>
#include "etc/env.h"
#include "GameWindow.h"

/// <summary>
/// Initializes a new instance of the <see cref="GameWindow"/> class.
/// </summary>
GameWindow::GameWindow(void)
{
    this->inited = false;
    this->GAMETIME_MULTIPLIER = 1.0;
    //Pointer safety
    this->window   = nullptr;
    this->renderer = nullptr;

    this->quit = false;
    this->CURRENT_FPS = 0;

    settings = IO::Settings ( IO::SETTING_LOAD_ON_REQUEST );
}


/// <summary>
/// Finalizes an instance of the <see cref="GameWindow"/> class.
/// </summary>
GameWindow::~GameWindow(void)
{
    if (this->inited) 
    {
        //Unload the Game Data
        this->Unload();

        //Destroy the window/renderer 
        SDL_DestroyRenderer ( this->renderer );
        SDL_DestroyWindow   ( this->window );

        //Shutdown inited services in reverse order of init
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

/// <summary>
/// Initializes Game Window.
/// </summary>
/// <param name="TITLE">Set the title of the Window.</param>
/// <param name="WIDTH">Set the width of the window.</param>
/// <param name="HIEGHT">Set the height of the window.</param>
/// <param name="Background">Set the background of the window.</param>
/// <param name="SDL_SCREEN_FLAGS">Start the window with given flags.</param>
/// <returns></returns>
int GameWindow::Init(const char* TITLE ,int WIDTH, int HIEGHT , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
    //If it already was inited, do not bother with it again
    if (this->inited)
        return 0;
    
    settings.load( SETTINGS_PATH , IO::SETTINGS_DUPLICATES_INGORED );
    
    //Support for Resizable windows 
    //Check if the settings contain the option
    if (settings.exists ( "render.screen" , "resizable" )) {
        //Evaluate if the option is set on
        if (settings.getBool ( "render.screen" , "resizable" )) {
            SDL_SCREEN_FLAGS |= SDL_WINDOW_RESIZABLE;
            
        }
    }
    
    //Support for fullscreen windows 
    //Check if the settings contain the option
    if (settings.exists ( "render.screen" , "fullscreen" )) {
        //Evaluate if the option is set on
        if (settings.getBool ( "render.screen" , "fullscreen" )) {
            SDL_SCREEN_FLAGS |=
//Build option to use SDL_WINDOW_FULLSCREEN
            		#ifdef GAME_WINDOW_USE_WINDOW_FULLSCREEN
            		SDL_WINDOW_FULLSCREEN;
#else
            		SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
        }
    }

    if (settings.exists ( "render.screen" , "display" ))
    {
    	SDL_setenv( "SDL_VIDEO_FULLSCREEN_DISPLAY" , settings.get ( "render.screen" , "display" ).c_str() , 0 );
    }

    //Start SDL
    if ( SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    
    //Start SDL_image
    if ( IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) == 0) 
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    //Start SDL_mixer
    if ( Mix_Init(MIX_INIT_MP3) == 0) 
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    //Start SDL_ttf
    if ( TTF_Init() == -1) 
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    
    //Create the window
    this->window = SDL_CreateWindow (  TITLE
                                     , SDL_WINDOWPOS_UNDEFINED
                                     , SDL_WINDOWPOS_UNDEFINED
                                     , WIDTH
                                     , HIEGHT
                                     , SDL_SCREEN_FLAGS );
    
    //Set minimum size of window (640x480)
    SDL_SetWindowMinimumSize( this->window ,640,480);
    
    //Check if the window was created
    if (this->window == nullptr)
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    int render_flags = SDL_RENDERER_ACCELERATED;
    //Support for SDL_Render VSync 
    //Check if the settings contain the option
    if (settings.exists ( "render.screen" , "vsync" )) {
        //Evaluate if the option is set on
        if (settings.getBool ( "render.screen" , "vsync" )) {
            render_flags |= SDL_RENDERER_PRESENTVSYNC;
        }
    }

    //Create Renderer
    this->renderer = SDL_CreateRenderer (this->window , -1 , render_flags );

    //Make sure it was created correctly
    if (this->renderer == nullptr)
    {
        std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    
    //Set background colour
    this->background = Background;

    this->inited = true;
    //All done correctly
    etc::printSystemInfo();
    return 0;
}

/// <summary>
/// Starts the game loop.
/// </summary>
void GameWindow::Start(void)
{
    //Load Content
    this->Load();

    SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
    SDL_RenderClear       (this->renderer);
    SDL_RenderPresent     (this->renderer);

    //Update Thread
    Timer fps = Timer();

    Timer delta = Timer();

    //Frame rate counter
    Timer counter = Timer();
    int counter_frames = 0;

    //Start Counter
    counter.start();

    //Start Delta
    delta.start();
    while (!this->quit)    //While not quitting, UPDATE!
    {
        //Start counting frame time for capping
        fps.start();

        //RENDERS HERE
        //Change in time in seconds with game-time multiplier to edit game speed
        double s_delta = (((double)(delta.get_ticks()) * GAMETIME_MULTIPLIER) / 1000.0);
        this->Update(s_delta);
        
        //Mid frame Check for exit
        if (this->quit)
            break;

        //Render delta for post-render
        s_delta = (((double)(delta.get_ticks()) * GAMETIME_MULTIPLIER) / 1000.0);
        this->Render(s_delta);
        SDL_RenderPresent(this->renderer);

        SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
        SDL_RenderClear  (this->renderer);

        //Restart Delta
        delta.start();

        //Increment frame count
        counter_frames++;

        if (counter.get_ticks() > 1000)   //1 second worth of frames collected
        {
            this->CURRENT_FPS = (int)(counter_frames / ( counter.get_ticks() / 1000.0 ));

            counter.start();
            counter_frames = 0;
        }
    }
}

/// <summary>
/// Loads the Game Window Data.
/// </summary>
void GameWindow::Load()
{
    
}

/// <summary>
/// Unloads the Game Window Data.
/// </summary>
void GameWindow::Unload()
{

}

/// <summary>
/// Renders the frame.
/// </summary>
/// <param name="delta">Change in time between last render.</param>
void GameWindow::Render(double delta)
{

}

/// <summary>
/// Updates the frame.
/// </summary>
/// <param name="delta">Change in time between last update.</param>
void GameWindow::Update(double delta)
{

    std::stringstream ss;
    ss << "Akaro (FPS:" << this->CURRENT_FPS << ")";

    SDL_SetWindowTitle ( this->window , ss.str().c_str() );

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        this->Event(event , delta);
    }
}

/// <summary>
/// Handles event.
/// </summary>
/// <param name="e">The SDL_Event.</param>
/// <param name="delta">Change in time between last update.</param>
void GameWindow::Event (SDL_Event e , double delta)
{
    switch (e.type)
    {
    case (SDL_QUIT):
        this->quit = true;
        break;
    case (SDL_KEYDOWN):
		if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            this->quit = true;
        }
    }
}
