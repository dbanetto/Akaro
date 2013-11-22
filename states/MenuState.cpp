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



MenuState::MenuState(GameStateManager* Manager, GameWindow* Window)
 : GameState()
{
    // TODO Auto-generated constructor stub
    this->manager = Manager;
    this->window = Window;
    this->font = nullptr;
}

MenuState::~MenuState()
{
    // TODO Auto-generated destructor stub
}

//Each frame
void MenuState::render (const double& delta, SDL_Renderer* renderer)
{
    bt.render(delta, renderer);
    lb.render(delta, renderer);

    sheep.render(delta, renderer);
    //SDL_RenderCopy(renderer , text.getTexture() , text.getSprite(0) , text.getSprite(0)  );

}

void MenuState::update (const double& delta)
{
    this->lb.setText( "FPS:" + etc::convInt (this->window->CURRENT_FPS) );
    this->bt.update(delta);

    if (this->window->getInputManager()->checkInput("sheep" , "up") == true)
    {
        sheep.setSpriteMapIndex(3);
        sheep.setFlip(SDL_FLIP_NONE);
    }
    if (this->window->getInputManager()->checkInput( "sheep" , "down") == true)
    {
        sheep.setSpriteMapIndex(2);
        sheep.setFlip(SDL_FLIP_NONE);
    }
    if (this->window->getInputManager()->checkInput( "sheep" , "left") == true)
    {
        sheep.setSpriteMapIndex(0);
        sheep.setFlip(SDL_FLIP_NONE);
    }
    if (this->window->getInputManager()->checkInput( "sheep" , "right") == true)
    {
        sheep.setSpriteMapIndex(0);
        sheep.setFlip(SDL_FLIP_HORIZONTAL);
    }
}

void MenuState::event (SDL_Event e , const double& delta)
{


}

//Inital un/Load Assests
void MenuState::load ()
{
    //TESTING ZONE
    std::string str = "";
    if ( this->window->getSettings()->get("ui" , "font" , &str) )
    {
        if  ( IO::fileExists ( str ) ) {
        this->font = TTF_OpenFont( str.c_str() , 16 );
        SDL_Point pt;
        pt.x = 0; pt.y = 0;
        this->lb = ui::Label ( "TEST" , this->font , pt );
        } else {
            std::cout << "Font Failed to load " << str << std::endl;
        }
    }
    SDL_Rect pt;
    pt.x = 100; pt.y = 100;
    pt.w = 100; pt.h = 100;
    SDL_Point lb_pt; lb_pt.x = 0; lb_pt.y = 0;
    this->bt = ui::Button(pt
                , etc::toColour( etc::COLOUR_GREEN)
                , etc::toColour( etc::COLOUR_BLUE)
                , 5
                , ui::Button::ButtonCallBacks()
                , ui::Label( "Button" , this->font , lb_pt ) );

    this->is_loaded = true;

    if ( this->window->getTextures()->load("data/texture/sheep.png" , "sheep" , 2 , 2) == false)
    {
        std::cout << "SHEEP Failed to load " << "data/texture/sheep.png" << std::endl;
    } else {
        SDL_Rect pos;
        pos.x = 50;
        pos.y = 50;
        pos.h = 32;
        pos.w = 32;

        SDL_Point cor;
        cor.x = 16;
        cor.y = 16;

        this->sheep = graphics::Sprite( this->window->getTextures()->getTexture("sheep") , pos, 0 , 0 , cor , SDL_FLIP_NONE );
    }
}

void MenuState::unload ()
{
    TTF_CloseFont( this->font );
    is_loaded = false;
}
