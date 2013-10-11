/*
 * Button.cpp
 *
 *  Created on: 9/10/2013
 *      Author: drb
 */

#include "Button.h"
#include <iostream>
namespace ui {

Button::Button() {
    // TODO Auto-generated constructor stub
    this->texture = nullptr;
    this->RENDER_BUTTON = true;
    this->pos.w = 100; this->pos.h = 100;
    this->pos.x = 100; this->pos.y = 100;

    this->fg.r = 0;
    this->fg.g = 255;
    this->fg.b = 0;

    this->border.r = 255;
    this->border.g = 0;
    this->border.b = 0;
    this->border_width = 1;

    this->button_events.button_clicked = nullptr;
    this->button_events.button_unclicked = nullptr;
    this->button_events.button_hover = nullptr;
    this->button_events.button_unhover = nullptr;
}

Button::Button( SDL_Rect pos , SDL_Color fg, SDL_Color border , int border_width , ButtonCallBacks callbacks , Label label )
{
    this->pos = pos;
    this->fg = fg;
    this->border = border;
    this->border_width = border_width;
    this->button_events = callbacks;
    this->label = label;

    this->texture = nullptr;
    this->RENDER_BUTTON = true;
}


Button::~Button() {
    // TODO Auto-generated destructor stub
}

void Button::render (const double& delta , SDL_Renderer* renderer )
{
    this->label.render(delta,renderer);

    SDL_SetRenderDrawColor( renderer , this->border.r , this->border.g ,  this->border.b ,  this->border.a );
    SDL_RenderFillRect(renderer , &this->pos );

    this->pos.x += this->border_width;
    this->pos.y += this->border_width;
    this->pos.w -= this->border_width*2;
    this->pos.h -= this->border_width*2;

    SDL_SetRenderDrawColor( renderer , this->fg.r , this->fg.g ,  this->fg.b ,  this->fg.a );
    SDL_RenderFillRect(renderer , &this->pos );

    this->pos.x -= this->border_width;
    this->pos.y -= this->border_width;
    this->pos.w += this->border_width*2;
    this->pos.h += this->border_width*2;

    CenterLabel( this->pos , &this->label );
    this->label.render( delta, renderer);

}

void Button::update (const double& delta )
{

}

} /* namespace ui */
