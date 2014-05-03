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
			#ifdef DEBUG
			std::cout << "Font loaded" << std::endl;
			#endif
		}
	}

	std::string tpath = "";
	if ( this->content->Settings()->get( "graphics" , "texturepack" , &tpath ) )
	{
		if ( this->window->getTextures()->loadList( tpath ) )
		{
			auto *tile = new map::MapTile::TileType();
			tile->name = "grass";
			tile->texture_name = "grass";

			if (this->content->TileTypes()->add ( "grass" , tile ))
			{
				#ifdef DEBUG
				std::cout << "Texture List Loaded" << std::endl;
				#endif
				if (this->content->Maps()->load( "demo" , "data/map.pam" ))
				{
						this->content->Maps()->setCurrentMap("demo");
						#ifdef DEBUG
						std::cout << "Map Loaded" << std::endl;
						#endif
				}
			}
		}
	} else {
		std::cout << "Could not find graphics.texturepack" << tpath << std::endl;
	}

	#ifdef DEBUG
	std::cout << "Menu State Loaded" << std::endl;
	#endif
	this->is_loaded = true;
}

void MenuState::unload ()
{
	this->is_loaded = false;
}
