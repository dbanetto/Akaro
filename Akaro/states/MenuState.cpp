/*
 * MenuState.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#include "MenuState.h"

#include "Engine/etc/env.h"
#include "Engine/etc/string.h"
#include "Engine/io/file.h"
#include "Engine/etc/colour.h"
#include "Engine/etc/Camera.h"

#include <iostream>

MenuState::MenuState( GameStateManager* Manager, GameWindow* Window , Content* Content )
	: GameState()
{
	this->manager = Manager;
	this->content = Content;
	this->window = Window;
}

MenuState::~MenuState()
{

}

//Each frame
void MenuState::render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera )
{

}

void MenuState::update ( const Ldouble& delta )
{

}

void MenuState::event ( SDL_Event e , const Ldouble& delta )
{


}

//Inital un/Load Assests
void MenuState::load ()
{

	std::string path = "";
	if ( this->content->Settings()->get( "ui" , "font" , &path ) )
	{
		if ( this->content->Fonts()->load( "ui.font" , path ) )
		{
			std::cout << "Font loaded" << std::endl;
		}
	}

	if (this->content->Audio()->load( "theme" , "ogg/abstract_anxiety.ogg" ))
	{
		this->content->Audio()->play("theme");
	}


	std::cout << "Menu State Loaded" << std::endl;
}

void MenuState::unload ()
{
	this->is_loaded = false;
}
