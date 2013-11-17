/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#include <iostream>
#include "etc/Timer.h"
#include <string>
#include <stdlib.h>
#include <sstream>
#include "etc/env.h"
#include "io/file.h"
#include "GameWindow.h"
#include "etc/string.h"
#include "etc/colour.h"
#include <iomanip>
#include <ctime>
#include "states/MenuState.h"
#include "input/KBProvider.h"
#include "input/PS3Provider.h"

/**
 * @brief Initializes a new instance of the GameWindow class.
 */
GameWindow::GameWindow(void)
{
    this->inited = false;
    this->GAMETIME_MULTIPLIER = 1.0;
    //Pointer safety
    this->window   = nullptr;
    this->renderer = nullptr;

    this->quit = false;
    this->CURRENT_FPS = -1;

    settings = IO::Settings ( IO::SETTING_LOAD_ON_REQUEST );



    //battery
    this->has_battery = false;
    this->last_battery_check = 0;
}


/**
 * @brief Finalizes an instance of the <see cref="GameWindow"/> class.
 */
GameWindow::~GameWindow(void)
{
    if (this->inited) 
    {
        //Clear Settings
        this->settings.clear();

        //Unload the Game Data
        this->unload();

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


/**
 * @brief Initializes Game Window.
 * @param TITLE Set the title of the Window.
 * @param Background Set the background of the window.
 * @param SDL_SCREEN_FLAGS Start the window with given flags.
 * @return Returns 0 on success.
 */
int GameWindow::init(const char* TITLE , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
    //If it already was inited, do not bother with it again
    if (this->inited)
        return 0;

    if (IO::fileExists( SETTINGS_PATH ) == false) {
        std::cout << TITLE << " could not initialize due to the settings file "
            << SETTINGS_PATH << " does not exist." ;
        return -1;
    }

    if (IO::fileExists( INPUT_SETTINGS_FILE ) == false) {
        std::cout << TITLE << " could not initialize due to the settings file "
            << INPUT_SETTINGS_FILE << " does not exist." ;
        return -1;
    }

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

    //Check if the System has a battery
    this->has_battery = etc::has_battery();

    this->textures = graphics::TextureManager(this->renderer);

    this->inited = true;
    //All done correctly

    return 0;
}

/**
 * @brief Starts the game loop.
 */
void GameWindow::start(void)
{
    //Load Content
    this->load();

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
        this->update(s_delta);
        
        //Mid frame Check for exit
        if (this->quit)
            break;

        //Render delta for post-render
        SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
        SDL_RenderClear  (this->renderer);

        s_delta = (((double)(delta.get_ticks()) * GAMETIME_MULTIPLIER) / 1000.0);

        this->render(s_delta);
        SDL_RenderPresent(this->renderer);

        //Assess render time

        //Restart Delta
        delta.start();

        //Increment frame count
        counter_frames++;

        if (counter.get_ticks() > 1000)   //1 second worth of frames collected
        {
            this->CURRENT_FPS = (int)(counter_frames / ( counter.get_ticks() / 1000.0 ));

            counter.start();
            counter_frames = 0;

            std::string error = SDL_GetError();
            if (error != "") {
                std::cout << "SDL Error : "<< error << std::endl;
            }
        }
    }
}


/**
 * @brief Loads the Game Window Data.
 */
void GameWindow::load()
{
    if (this->has_battery && this->settings.exists("battery"))
    {
        //Load Battery Settings
        this->settings.load_section( "battery" , IO::SETTINGS_DUPLICATES_INGORED );

        //Set the warning level
        if ( this->settings.exists("battery" , "warn") )
        {
            std::string warn_amount;
            this->settings.get("battery" , "warn" , &warn_amount);

            //If it is a percentage
            if (etc::endswith(warn_amount , "%"))
            {
                //Remove the %
                warn_amount = warn_amount.substr( 0 , warn_amount.length() - 2 );
                int perc = atoi (warn_amount.c_str());
                etc::batterySetWarningPercent( perc );
            } else {
                //Time amount
                etc::batterySetWarningTime( etc::timeToInt( warn_amount ) );
            }
        }

        //Set the check interval
        if ( this->settings.exists("battery" , "interval") )
        {
            std::string warn_interval;
            this->settings.get("battery" , "interval" , &warn_interval);
            etc::batterySetCheckInterval( etc::timeToInt( warn_interval ) );
        }

        //Check if this feature is wanted to be enabled
        if ( this->settings.exists("battery" , "enable") )
        {
            bool enable_bat = false;
            this->settings.getBool( "battery" , "enable" , &enable_bat );
            //If the settings say disable, the battery check in GameWindow is disabled
            this->has_battery = enable_bat;
        }

    }

    etc::printSystemInfo();

    //INPUT
    input.load( INPUT_SETTINGS_FILE , IO::SETTINGS_DUPLICATES_INGORED , IO::SETTING_LOAD_ON_REQUEST);
    input.add_provider("kb" , new input::KBProvider() );
    input.add_provider("ps3" , new input::PS3Provider() );
    //GAME STATES
    this->gamestate.add_state( "menu" ,  new MenuState(&(this->gamestate) , (this)) );
    this->gamestate.set_state( "menu" );

    audio.load_settings( &(this->settings) );
}

/**
 * @brief Unloads the Game Window Data.
 */
void GameWindow::unload()
{
    if (this->gamestate.current != nullptr)
    {
        this->gamestate.current->unload();
    }

    this->audio.unloadall();
}

/**
 * @brief Renders the frame.
 * @param delta Change in time between last render.
 */
void GameWindow::render(const double& delta)
{
    if (this->gamestate.current != nullptr)
    {
        this->gamestate.current->render(delta, this->renderer);
    }
}

/**
 * @brief Updates the Game for the frame.
 * @param delta Change in time between last update.
 */
void GameWindow::update(const double& delta)
{
    if (this->has_battery == true) {
        if (this->last_battery_check >= etc::batteryGetCheckInterval())
        {
            this->last_battery_check = 0;
            if (etc::batteryStatus() == BATTERY_WARNING) {
                //BATTERY WARNING! DO SOMETHING ABOUT IT!!!
                std::cout << "Warning! Battery is about to run out!" << std::endl ;
            }

        } else {
            this->last_battery_check += delta;
        }
    }



    SDL_PumpEvents();
    this->input.update(delta);

    if (this->gamestate.current != nullptr)
    {
        this->gamestate.current->update(delta);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        this->event(event , delta);
    }
}

/**
 * @brief Handles SDL events
 * @param e The SDL_Event.
 * @param delta Change in time between last update.
 */
void GameWindow::event (SDL_Event e , const double& delta)
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
        if (e.key.keysym.sym == SDLK_F12)
        {
            this->screenshot();
        }
        break;
    case (SDL_MOUSEBUTTONDOWN):
        //Fire Click Event
        break;
    }
}

/**
 * @brief Takes a screenshot of the current rendered screen and then saves it to a .bmp
 */
void GameWindow::screenshot()
{
    //Skip the screenshot if the Game Window is not inited
    if(this->inited == false)
    {
        return;
    }

    SDL_Rect clip;
    clip.x = 0; clip.y = 0;

    //Get the size of the screen to be taken
    SDL_GetWindowSize(this->window , &clip.w , &clip.h );

    //Get the window surface
    SDL_Surface* surface = SDL_GetWindowSurface(this->window);

    //Make sire you have the surface
    if (surface == NULL) {
        std::cout << "SDL Render Error : " << SDL_GetError() << std::endl;
        return;
    }

    //Copy the pixels in the renderer to the surface's pixels
    SDL_RenderReadPixels(this->renderer , &clip , SDL_GetWindowPixelFormat(this->window) , surface->pixels , surface->pitch );

    //Save the bitmap
    //TODO: Improve Naming Scheme
    std::stringstream ss;
#ifdef STD_PUT_TIME
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    ss << "akora-" << std::put_time(&tm, "%Y-%m-%d %H-%M-%S") << ".bmp";
#else
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%Y-%m-%d %H-%M-%S",timeinfo);

    ss << "akora-" << etc::trim( std::string(buffer) ) << ".bmp";
#endif
    SDL_SaveBMP( surface , ss.str().c_str() );
    //Tidy up surface
    SDL_FreeSurface( surface );


}
/**
 * @brief Returns a pointer to the Window Settings
 */
IO::Settings* GameWindow::getSettings ()
{
    return &(this->settings);
}

graphics::TextureManager* GameWindow::getTextures()
{
    return &(this->textures);
}

input::InputManager * GameWindow::getInputManager()
{
    return &(this->input);
}
audio::AudioManager* GameWindow::getAudio()
{
    return &(this->audio);
}
