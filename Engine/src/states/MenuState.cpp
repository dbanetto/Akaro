/*
 * MenuState.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#include "MenuState.h"
#include "../etc/env.h"
#include "../etc/string.h"
#include "../io/file.h"
#include <iostream>
#include "../etc/colour.h"
#include "../etc/Camera.h"



MenuState::MenuState(GameStateManager* Manager, GameWindow* Window, Content* ccontent)
	: GameState()
{
	this->manager = Manager;
	this->window = Window;
	this->content = ccontent;
	this->font = nullptr;
}

MenuState::~MenuState()
{

}

//Each frame
void MenuState::render (const Ldouble& delta, SDL_Renderer* renderer , etc::Camera &camera )
{
	camera.setPosition(sheep.getRect().x -100, sheep.getRect().y - 100);

	this->map.render(delta, renderer , camera);

	bt.render(delta, renderer , camera);
	lb.render(delta, renderer , camera);

	sheep.render(delta, renderer , camera);

}

#define SPEED 200.0

void MenuState::update (const Ldouble& delta)
{
	this->lb.setText( "FPS:" + etc::convInt (this->window->CURRENT_FPS) );
	this->bt.update(delta);
	this->map.update(delta);

	if (this->content->Input()->checkInput("sheep" , "up") == true)
	{
		sheep.setSpriteMapIndex(3);
		sheep.changePosition(0,-SPEED*delta);
		sheep.setFlip(SDL_FLIP_NONE);
	}
	if (this->content->Input()->checkInput( "sheep" , "down") == true)
	{
		sheep.setSpriteMapIndex(2);
		sheep.changePosition(0,SPEED*delta);
		sheep.setFlip(SDL_FLIP_NONE);
	}
	if (this->content->Input()->checkInput( "sheep" , "left") == true)
	{
		sheep.setSpriteMapIndex(0);
		sheep.changePosition(-SPEED*delta,0);
		sheep.setFlip(SDL_FLIP_NONE);
	}
	if (this->content->Input()->checkInput( "sheep" , "right") == true)
	{
		sheep.setSpriteMapIndex(0);
		sheep.changePosition(SPEED*delta,0);
		sheep.setFlip(SDL_FLIP_HORIZONTAL);
	}
}

void MenuState::event (SDL_Event e , const Ldouble& delta)
{


}

//Inital un/Load Assests
void MenuState::load ()
{
	//TESTING ZONE
	std::string str = "";
	if ( this->content->Settings()->get("ui" , "font" , &str) )
	{
		if  ( IO::fileExists ( str ) )
		{
			this->font = TTF_OpenFont( str.c_str() , 16 );
			SDL_Point pt;
			pt.x = 0;
			pt.y = 0;
			this->lb = ui::Label ( "TEST" , this->font , pt );
		}
		else
		{
			std::cout << "Font Failed to load " << str << std::endl;
		}
	}
	SDL_Rect pt;
	pt.x = 100;
	pt.y = 100;
	pt.w = 100;
	pt.h = 100;
	SDL_Point lb_pt;
	lb_pt.x = 0;
	lb_pt.y = 0;
	this->bt = ui::Button(pt
						  , etc::toColour( etc::COLOUR_GREEN)
						  , etc::toColour( etc::COLOUR_BLUE)
						  , 5
						  , ui::Button::ButtonCallBacks()
						  , ui::Label( "Button" , this->font , lb_pt ) );
	this->bt.setAdjustCamera(true);

	this->is_loaded = true;

	if ( this->window->getTextures()->load("data/texture/sheep.png" , "sheep" , 2 , 2) == false)
	{
		std::cout << "SHEEP Failed to load " << "data/texture/sheep.png" << std::endl;
	}
	else
	{
		SDL_Rect pos;
		pos.x = 50;
		pos.y = 50;
		pos.h = 32;
		pos.w = 32;

		SDL_Point cor;
		cor.x = 16;
		cor.y = 16;

		this->sheep = graphics::Sprite( this->window->getTextures()->getTexture("sheep") , pos, 0 , 0 , cor , SDL_FLIP_NONE );
		this->sheep.setAdjustCamera(true);
	}

	this->window->getTextures()->load("data/texture/grass.png" , "grass" , 2 , 2);
	this->map.init(this->window->getTextures());
	this->map.loadMap("data/map.pam");
}

void MenuState::unload ()
{
	this->is_loaded = false;
	this->map.unloadMap();
	if (this->font != nullptr)
	{
		TTF_CloseFont( this->font );
		this->font = nullptr;
	}

}
