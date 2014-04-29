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
	if (!this->is_loaded)
		return;

	this->content->Maps()->get("demo")->render( delta , this->window->getTextures() , camera);
}

void MenuState::update ( const Ldouble& delta )
{
	if (!this->is_loaded)
		return;
}

void MenuState::event ( SDL_Event e , const Ldouble& delta )
{
	if (!this->is_loaded)
		return;

}

//Inital un/Load Assests
void MenuState::load ()
{

	std::string path = "";
	{
	if ( this->content->Settings()->get( "ui" , "font" , &path ) )
		if ( this->content->Fonts()->load( "ui" , path ) )
		{
			std::cout << "Font loaded" << std::endl;
		}
	}

	std::string tpath = "";
	if ( this->content->Settings()->get( "graphics" , "texturepack" , &tpath ) )
	{
		if ( this->window->getTextures()->loadList( tpath ) )
		{
			std::cout << "Texture List Loaded" << std::endl;
			if (this->content->Maps()->load( "demo" , "data/map.pam" ))
			{
				this->content->Maps()->setCurrentMap("demo");
				std::cout << "Map Loaded" << std::endl;
			}
		}
	} else {
		std::cout << "Could not find graphics.texturepack" << tpath << std::endl;
	}

	this->content->Audio()->load( "theme" , "ogg/abstract_anxiety.ogg" );
	this->content->Audio()->play("theme");

	std::cout << "Menu State Loaded" << std::endl;
	this->is_loaded = true;
}

void MenuState::unload ()
{
	this->content->Audio()->stop("theme");
	this->is_loaded = false;
}
