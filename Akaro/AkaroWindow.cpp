/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include "AkaroWindow.h"
#include "states/MenuState.h"
#include "states/WorldState.h"
#include "input/KBProvider.h"
#include "input/PS3Provider.h"

#include <iostream>

AkaroWindow::AkaroWindow(Content* content)
	: GameWindow(content)
{

}

AkaroWindow::~AkaroWindow(void)
{

}


/**
 * @brief Initializes Game Window.
 * @param TITLE Set the title of the Window.
 * @param Background Set the background of the window.
 * @param SDL_SCREEN_FLAGS Start the window with given flags.
 * @return Returns 0 on success.
 */
int AkaroWindow::init(const char* TITLE , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
	return GameWindow::init(TITLE,Background,SDL_SCREEN_FLAGS);
}

/**
 * @brief Starts the game loop.
 */
void AkaroWindow::start(void)
{
	GameWindow::start();
}


/**
 * @brief Loads the Game Window Data.
 */
void AkaroWindow::load()
{
	GameWindow::load();

	this->content->Input()->load( INPUT_SETTINGS_FILE , IO::SETTINGS_DUPLICATES_INGORED , IO::SETTING_LOAD_ON_REQUEST);
	if (this->content->Settings()->exists("Controller" , "ps3.enable"))
	{
		bool enable = false;
		this->content->Settings()->getBool( "Controller" , "ps3.enable" , &enable );
		if (enable)
		{
			if (this->content->Input()->add_provider("ps3" , new input::PS3Provider() ) == false)
			{
				std::cout << "Failed to load Playstation 3 Controller" << std::endl;
			}
		}
	}

	if (this->content->Input()->add_provider("kb" , new input::KBProvider() ) == false )
	{
		std::cout << "Failed to load Keyboard" << std::endl;
	}

	std::cout << "Input loaded" << std::endl;

	//GAME STATES
	this->content->Gamestate()->add_state( "menu" ,   new MenuState( this->content->Gamestate(), this, this->content ) );
	this->content->Gamestate()->add_state( "world" , new WorldState( this->content->Gamestate(), this, this->content ) );

	this->content->Gamestate()->set_state("menu");
}

/**
 * @brief Unloads the Game Window Data.
 */
void AkaroWindow::unload()
{
    GameWindow::unload();
}

/**
 * @brief Renders the frame.
 * @param delta Change in time between last render.
 */
void AkaroWindow::render(const Ldouble& delta)
{
	GameWindow::render(delta);
}

/**
 * @brief Updates the Game for the frame.
 * @param delta Change in time between last update.
 */
void AkaroWindow::update(const Ldouble& delta)
{
	GameWindow::update(delta);
}

/**
 * @brief Handles SDL events
 * @param e The SDL_Event.
 * @param delta Change in time between last update.
 */
void AkaroWindow::event (SDL_Event e , const double& delta)
{
	GameWindow::event(e,delta);
}
