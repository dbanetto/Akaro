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
#include "io/file.h"
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
    	//Clear Settings
    	this->settings.clear();

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
int GameWindow::Init(const char* TITLE , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
    //If it already was inited, do not bother with it again
    if (this->inited)
        return 0;

    if (IO::fileExists( SETTINGS_PATH ) == false) {
    	std::cout << TITLE << " could not initialize due to the settings file " << SETTINGS_PATH << " does not exist." ;
    	return -1;
    }

    if (IO::fileExists( INPUT_SETTINGS_FILE ) == false) {
    	std::cout << TITLE << " could not initialize due to the settings file " << INPUT_SETTINGS_FILE << " does not exist." ;
    	return -1;
    }

    input.load( INPUT_SETTINGS_FILE , IO::SETTINGS_DUPLICATES_INGORED );
    settings.load( SETTINGS_PATH , IO::SETTINGS_DUPLICATES_INGORED );
    
    //Support for Resizable windows 
    //Check if the settings contain the option
    bool resizable;
    if (settings.getBool ( "window" , "resizable" , &resizable ) == true)
    {
        //Evaluate if the option is set on
        if (resizable) {
            SDL_SCREEN_FLAGS |= SDL_WINDOW_RESIZABLE;
            
        }
    }
    
    //Support for fullscreen windows 
    //Check if the settings contain the option
    bool fullscreen;
    if (settings.getBool ( "window" , "fullscreen", &fullscreen ) == true)
    {
        //Evaluate if the option is set on
        if (fullscreen) {
            SDL_SCREEN_FLAGS |=
//Build option to use SDL_WINDOW_FULLSCREEN instead of DESKTOP
            		#ifdef GAME_WINDOW_USE_WINDOW_FULLSCREEN
            		SDL_WINDOW_FULLSCREEN;
#else
            		SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
        }
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
    
    int display = 0;
    settings.getInt ( "window" , "display" , &display );


    //Set display to be rendered to
     SDL_DisplayMode display_mode;
 	if ( SDL_GetDisplayMode( display , 0 , &display_mode ) != 0)
 	{
 		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
 	}

    int WIDTH = 800;
	if (this->settings.getInt( "window" , "width" , &WIDTH ) == false)
	{
		std::string native;
		if (this->settings.get ("window" , "width" , &native) == true)
		{
			if (native == "native") {
				//Set height as native screen height
				SDL_DisplayMode dm;
				if ( SDL_GetDesktopDisplayMode(display , &dm ) == 0)
				{
					WIDTH = dm.w;
				}
			}
		}
		if (WIDTH == 800) {
			std::cout << "Warning! Window width is set to default, 800px" << std::endl;
		}
	}

	int HIEGHT = 600;
    if (this->settings.getInt( "window" , "height" , &HIEGHT ) == false)
    {
    	std::string native;
    	if (this->settings.get ("window" , "height" , &native) == true)
    	{
    		if (native == "native") {
    			//Set height as native screen height
    			SDL_DisplayMode dm;
    			if ( SDL_GetDesktopDisplayMode( display , &dm ) == 0)
    			{
    				HIEGHT = dm.h;
    			}
    		}
    	}
    	if (HIEGHT == 600)
    	{
    		std::cout << "Warning! Window height is set to default, 600px" << std::endl;
    	}
    }


    //Create the window
    this->window = SDL_CreateWindow (  TITLE
                                     , SDL_WINDOWPOS_CENTERED_DISPLAY(display)
                                     , SDL_WINDOWPOS_CENTERED_DISPLAY(display)
                                     , WIDTH
                                     , HIEGHT
                                     , SDL_SCREEN_FLAGS );
    
    //Set minimum size of window (640x480)
    SDL_SetWindowMinimumSize( this->window ,640,480);
    SDL_SetWindowDisplayMode( this->window , &display_mode );

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
    bool vsync;
    if (settings.getBool ( "window" , "vsync" , &vsync))
    {
        //Evaluate if the option is set on
        if (vsync)
        {
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

    etc::printSystemInfo();

    this->inited = true;
    //All done correctly

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
