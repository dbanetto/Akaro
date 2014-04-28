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
#include <iomanip>
#include <ctime>
#include <cmath>

#include "io/file.h"
#include "GameWindow.h"
#include "etc/string.h"
#include "etc/colour.h"

/**
 * @brief Initializes a new instance of the GameWindow class.
 */
GameWindow::GameWindow( Content* content )
{
	this->inited = false;
	this->GAMETIME_MULTIPLIER = 1.0;
	//Pointer safety
	this->window   = nullptr;
	this->renderer = nullptr;

	this->quit = false;
	this->CURRENT_FPS = -1;

	CAP_FRAMES = false;
	this->FRAME_LIMIT = 0;

	//battery
	this->has_battery = false;
	this->last_battery_check = 0;

	this->content = content;
}


/**
 * @brief Finalizes an instance of the <see cref="GameWindow"/> class.
 */
GameWindow::~GameWindow( void )
{
	if ( this->inited )
	{
		//Unload the Game Data
		this->unload();

		//Destroy the window/renderer
		SDL_DestroyRenderer ( this->renderer );
		SDL_DestroyWindow   ( this->window );
	}
}


/**
 * @brief Initializes Game Window.
 * @param TITLE Set the title of the Window.
 * @param Background Set the background of the window.
 * @param SDL_SCREEN_FLAGS Start the window with given flags.
 * @return Returns 0 on success.
 */
int GameWindow::init( const char* TITLE , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
	//If it already was inited, do not bother with it again
	if ( this->inited )
		return 0;

	//Support for Resizeable windows
	//Check if the settings contain the option
	bool resizable;
	if ( this->content->Settings()->getBool ( "window" , "resizeable" , &resizable ) == true )
	{
		//Evaluate if the option is set on
		if ( resizable )
		{
			SDL_SCREEN_FLAGS |= SDL_WINDOW_RESIZABLE;

		}
	}

	//Support for fullscreen windows
	//Check if the settings contain the option
	bool fullscreen;
	if ( this->content->Settings()->getBool ( "window" , "fullscreen", &fullscreen ) == true )
	{
		//Evaluate if the option is set on
		if ( fullscreen )
		{
			SDL_SCREEN_FLAGS |=
//Build option to use SDL_WINDOW_FULLSCREEN instead of DESKTOP
#ifdef GAME_WINDOW_USE_WINDOW_FULLSCREEN
				SDL_WINDOW_FULLSCREEN;
#else
				SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
		}
	}

	int display = 0;
	this->content->Settings()->getInt ( "window" , "display" , &display );


	//Set display to be rendered to
	SDL_DisplayMode display_mode;
	if ( SDL_GetDisplayMode( display , 0 , &display_mode ) != 0 )
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
	}

	int WIDTH = 800;
	if ( this->content->Settings()->getInt( "window" , "width" , &WIDTH ) == false )
	{
		std::string native;
		if ( this->content->Settings()->get ( "window" , "width" , &native ) == true )
		{
			if ( native == "native" )
			{
				//Set height as native screen height
				SDL_DisplayMode dm;
				if ( SDL_GetDesktopDisplayMode( display , &dm ) == 0 )
				{
					WIDTH = dm.w;
				}
			}
		}
		if ( WIDTH == 800 )
		{
			std::cout << "Warning! Window width is set to default, 800px" << std::endl;
		}
	}

	int HIEGHT = 600;
	if ( this->content->Settings()->getInt( "window" , "height" , &HIEGHT ) == false )
	{
		std::string native;
		if ( this->content->Settings()->get ( "window" , "height" , &native ) == true )
		{
			if ( native == "native" )
			{
				//Set height as native screen height
				SDL_DisplayMode dm;
				if ( SDL_GetDesktopDisplayMode( display , &dm ) == 0 )
				{
					HIEGHT = dm.h;
				}
			}
		}
		if ( HIEGHT == 600 )
		{
			std::cout << "Warning! Window height is set to default, 600px" << std::endl;
		}
	}


	//Create the window
	this->window = SDL_CreateWindow (  TITLE
									   , SDL_WINDOWPOS_CENTERED_DISPLAY( display )
									   , SDL_WINDOWPOS_CENTERED_DISPLAY( display )
									   , WIDTH
									   , HIEGHT
									   , SDL_SCREEN_FLAGS );

	//Set minimum size of window (640x480)
	SDL_SetWindowMinimumSize( this->window , 640, 480 );
	SDL_SetWindowDisplayMode( this->window , &display_mode );

	//Check if the window was created
	if ( this->window == nullptr )
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}

	int render_flags = SDL_RENDERER_ACCELERATED;
	//Support for SDL_Render VSync
	//Check if the settings contain the option
	bool vsync;
	if ( this->content->Settings()->getBool ( "window" , "vsync" , &vsync ) )
	{
		//Evaluate if the option is set on
		if ( vsync )
		{
			//render_flags |= SDL_RENDERER_PRESENTVSYNC;
			this->CAP_FRAMES = true;
		}
	}

	int FRAME_LIMIT = display_mode.refresh_rate;
	if ( this->content->Settings()->getInt ( "window" , "framelimit" , &FRAME_LIMIT ) )
	{
		std::cout << FRAME_LIMIT << std::endl;
		if ( FRAME_LIMIT > 0 )
		{
			this->FRAME_LIMIT = FRAME_LIMIT;
		}
		else
		{
			std::cout << "Cannot set negative Frame Limit " << FRAME_LIMIT << std::endl;
		}
	}
	else
	{
		this->FRAME_LIMIT = FRAME_LIMIT;
	}

	//Create Renderer
	this->renderer = SDL_CreateRenderer ( this->window , 1 , render_flags );

	//Make sure it was created correctly
	if ( this->renderer == nullptr )
	{
		std::cout << "An error has occurred" << std::endl << SDL_GetError() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}

	//Set background colour
	this->background = Background;

	//Check if the System has a battery
	this->has_battery = etc::has_battery();

	//Camera bnounds
	this->camera.setBounds( WIDTH , HIEGHT );
	this->camera.setPosition( 0, 0 );

	this->content->load(this->renderer);

	this->inited = true;
	//All done correctly

	return 0;
}

/**
 * @brief Starts the game loop.
 */
void GameWindow::start( void )
{
	//Load Content
	this->load();

	SDL_SetRenderDrawColor( this->renderer, this->background.r, this->background.g, this->background.b, this->background.a );
	SDL_RenderClear       ( this->renderer );
	SDL_RenderPresent     ( this->renderer );

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
	while ( !this->quit )  //While not quitting, UPDATE!
	{
		//Start counting frame time for capping
		fps.start();

		//RENDERS HERE
		//Change in time in seconds with game-time multiplier to edit game speed
		Ldouble s_delta = delta.get_ticks() * GAMETIME_MULTIPLIER;
		this->update( s_delta );

		//Mid frame Check for exit
		if ( this->quit )
			break;

		//Render delta for post-render
		SDL_SetRenderDrawColor( this->renderer, this->background.r, this->background.g, this->background.b, this->background.a );
		SDL_RenderClear  ( this->renderer );

		s_delta = delta.get_ticks() * GAMETIME_MULTIPLIER;
		this->render( s_delta );
		SDL_RenderPresent( this->renderer );

		//Assess render time

		//Restart Delta
		delta.start();

		//Increment frame count
		counter_frames++;

		if( ( this->CAP_FRAMES == true ) )
		{
			if ( fps.get_ticks() < 1000.0 / this->FRAME_LIMIT )
			{
				//Sleep the remaining frame time
				Uint32 delay = ( Uint32 )( round( ( 1000.0 / this->FRAME_LIMIT ) - ( fps.get_ticks() * 1000 ) ) );

				//Correct the time to sleep so it keeps up where the frame is suppose to be in terms of a second
				//Uint32 normaliser =  (Uint32)round( counter.get_ticks() ) - (Uint32)round( ( counter_frames / this->FRAME_LIMIT) );
				//Only Apply it if it is needed
				//if ( normaliser < delay && normaliser != 0 )
				//{
				//	delay -= normaliser;
				//}
				//Crash safety net and is less than a second
				if ( delay > 0 && delay < 1000 )
				{
					SDL_Delay(  delay );
				}
			}
			else
			{
				std::cout << "Cannot Keep up!" << std::endl;
			}
		}
		else
		{
			SDL_Delay(  1 );
		}
		if ( counter.get_ticks() > 1 ) //1 second worth of frames collected
		{
			this->CURRENT_FPS = counter_frames / counter.get_ticks();
#ifdef VERBOSE_FRAME_TIME
			if ( this->CAP_FRAMES )
			{
				std::cout << "Taken:" << counter.get_ticks() / CURRENT_FPS * 1000.0 << "ms Expected:" << 1.0 / this->FRAME_LIMIT * 1000.0  << "ms " <<
						  ( 1.0 / this->FRAME_LIMIT * 1000.0 ) /  ( counter.get_ticks() / CURRENT_FPS * 1000.0 ) * 100 << "%" << std::endl;
			}
#endif
			counter.start();
			counter_frames = 0;

			std::string error = SDL_GetError();
			if ( error != "" )
			{
				std::cout << "SDL Error : " << error << std::endl;
				SDL_ClearError();
			}
		}
	}
	this->unload();
}


/**
 * @brief Loads the Game Window Data.
 */
void GameWindow::load()
{
	if ( this->has_battery && this->content->Settings()->exists( "battery" ) )
	{
		//Load Battery Settings
		this->content->Settings()->load_section( "battery" , IO::SETTINGS_DUPLICATES_INGORED );

		//Set the warning level
		if ( this->content->Settings()->exists( "battery" , "warn" ) )
		{
			std::string warn_amount;
			this->content->Settings()->get( "battery" , "warn" , &warn_amount );

			//If it is a percentage
			if ( etc::endswith( warn_amount , "%" ) )
			{
				//Remove the %
				warn_amount = warn_amount.substr( 0 , warn_amount.length() - 2 );
				int perc = atoi ( warn_amount.c_str() );
				etc::batterySetWarningPercent( perc );
			}
			else
			{
				//Time amount
				etc::batterySetWarningTime( etc::timeToInt( warn_amount ) );
			}
		}

		//Set the check interval
		if ( this->content->Settings()->exists( "battery" , "interval" ) )
		{
			std::string warn_interval;
			this->content->Settings()->get( "battery" , "interval" , &warn_interval );
			etc::batterySetCheckInterval( etc::timeToInt( warn_interval ) );
		}

		//Check if this feature is wanted to be enabled
		if ( this->content->Settings()->exists( "battery" , "enable" ) )
		{
			bool enable_bat = false;
			this->content->Settings()->getBool( "battery" , "enable" , &enable_bat );
			//If the settings say disable, the battery check in GameWindow is disabled
			this->has_battery = enable_bat;
		}
	}
}

/**
 * @brief Unloads the Game Window Data.
 */
void GameWindow::unload()
{

}

/**
 * @brief Renders the frame.
 * @param delta Change in time between last render.
 */
void GameWindow::render( const Ldouble& delta )
{
	if ( this->content->Gamestate()->current != nullptr )
	{
		this->content->Gamestate()->current->render( delta, this->renderer , this->camera );
	}
}

/**
 * @brief Updates the Game for the frame.
 * @param delta Change in time between last update.
 */
void GameWindow::update( const Ldouble& delta )
{
	if ( this->has_battery == true )
	{
		if ( this->last_battery_check >= etc::batteryGetCheckInterval() )
		{
			this->last_battery_check = 0;
			if ( etc::batteryStatus() == BATTERY_WARNING )
			{
				//BATTERY WARNING! DO SOMETHING ABOUT IT!!!
				std::cout << "Warning! Battery is about to run out!" << std::endl ;
			}

		}
		else
		{
			this->last_battery_check += delta;
		}
	}



	SDL_PumpEvents();
	this->content->Input()->update( delta );

	if ( this->content->Gamestate()->current != nullptr )
	{
		this->content->Gamestate()->current->update( delta );
	}

	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		this->event( event , delta );
	}
}

/**
 * @brief Handles SDL events
 * @param e The SDL_Event.
 * @param delta Change in time between last update.
 */
void GameWindow::event ( SDL_Event e , const double& delta )
{
	switch ( e.type )
	{
		case ( SDL_QUIT ):
			this->quit = true;
			break;
		case ( SDL_KEYDOWN ):
			if ( this->content->Input()->checkInput( "core", "qquit" ) )
			{
				this->quit = true;
			}
			if ( this->content->Input()->checkInput( "core", "screenshot" ) )
			{
				this->screenshot();
			}
			break;
		case ( SDL_WINDOWEVENT ):
			int w = 0, h = 0;
			SDL_GetWindowSize( this->window, &w, &h );
			this->camera.setBounds( w, h );
	}
}

/**
 * @brief Takes a screenshot of the current rendered screen and then saves it to a .bmp
 */
void GameWindow::screenshot()
{
	//Skip the screenshot if the Game Window is not inited
	if( this->inited == false )
	{
		return;
	}

	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;

	//Get the size of the screen to be taken
	SDL_GetWindowSize( this->window , &clip.w , &clip.h );

	//Get the window surface
	SDL_Surface* surface = SDL_GetWindowSurface( this->window );

	//Make sire you have the surface
	if ( surface == NULL )
	{
		std::cout << "SDL Render Error : " << SDL_GetError() << std::endl;
		return;
	}

	//Copy the pixels in the renderer to the surface's pixels
	SDL_RenderReadPixels( this->renderer , &clip , SDL_GetWindowPixelFormat( this->window ) , surface->pixels , surface->pitch );

	//Save the bitmap
	//TODO: Improve Naming Scheme
	std::stringstream ss;
#ifdef STD_PUT_TIME
	std::time_t t = std::time( nullptr );
	std::tm tm = *std::localtime( &t );
	ss << "akora-" << std::put_time( &tm, "%Y-%m-%d %H-%M-%S" ) << ".bmp";
#else
	time_t rawtime;
	struct tm* timeinfo;
	char buffer [80];

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strftime ( buffer, 80, "%Y-%m-%d %H-%M-%S", timeinfo );

	ss << "akora-" << etc::trim( std::string( buffer ) ) << ".bmp";
#endif
	SDL_SaveBMP( surface , ss.str().c_str() );
	//Tidy up surface
	SDL_FreeSurface( surface );


}
