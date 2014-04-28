/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include "AkaroWindow.h"
#include "states/MenuState.h"


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

	//GAME STATES
	this->content->Gamestate()->add_state( "menu" ,  new MenuState( this->content->Gamestate()  , (this)  , this->content ) );
	this->content->Gamestate()->set_state( "menu" );
	this->content->Gamestate()->current->load();
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
