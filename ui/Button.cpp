/*
 * Button.cpp
 *
 *  Created on: 9/10/2013
 *      Author: drb
 */

#include "Button.h"
#include "../etc/colour.h"
#include <iostream>
namespace ui {

Button::Button() {
    this->texture = nullptr;
    this->RENDER_TEXTURE = true;
    this->area.w = 100; this->area.h = 100;
    this->area.x = 100; this->area.y = 100;

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

    this->UPDATE_POSITION = true;
}

/**
 * @param pos Position of button
 * @param fg Foreground colour
 * @param border Border colour
 * @param border_width Border width
 * @param callbacks A collection of callback functions
 * @param label Label to be rendered in the button (can be null)
 */
Button::Button( SDL_Rect pos , SDL_Color fg, SDL_Color border , int border_width , ButtonCallBacks callbacks , Label label )
{
    this->area = pos;
    this->fg = fg;
    this->border = border;
    this->border_width = border_width;

    this->button_events.button_clicked = callbacks.button_clicked;
    this->button_events.button_unclicked = callbacks.button_unclicked;
    this->button_events.button_hover = callbacks.button_hover;
    this->button_events.button_unhover = callbacks.button_unhover;

    this->label = label;

    this->texture = nullptr;
    this->RENDER_TEXTURE = true;
    this->UPDATE_POSITION = true;
}


Button::~Button() {
}
/**
 * @brief
 * @param delta
 * @param renderer
 */
void Button::render (const Ldouble& delta , SDL_Renderer* renderer )
{
    if (this->RENDER_TEXTURE == true) {
        //If the Label has a texture destroy it FOR SAFETY! border
        if (this->texture != nullptr) {
            SDL_DestroyTexture(this->texture);
        }
        this->texture = generateButtonTexture( renderer , this->fg , this->border , this->border_width, this->area );
        this->RENDER_TEXTURE = false;
    }

    SDL_RenderCopy( renderer , this->texture , NULL , &(this->area) );

    this->label.render(delta,renderer);
}

void Button::update (const Ldouble& delta )
{
    //Check if the Button needs an update
    if (this->UPDATE_POSITION == true) {
        centerLabel( this->area , &this->label );
        this->pos.x = area.x;
        this->pos.y = area.y;
        this->UPDATE_POSITION = false;
    }
    //Check if Label needed an update
    if (this->label.UPDATE_POSITION == true) {
        centerLabel( this->area , &this->label );
        this->pos.x = area.x;
        this->pos.y = area.y;
        this->label.UPDATE_POSITION = false;
    }
}

//Byte Order
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

SDL_Texture* generateButtonTexture (SDL_Renderer* renderer , SDL_Color fg , SDL_Color border, int border_width , SDL_Rect area )
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0, area.w, area.h, 32,
                             rmask, gmask, bmask, amask);
    if (surface == NULL) {
        std::cout << "SDL Render Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    //Create a software Render with target of surface
    SDL_Renderer* swRender = SDL_CreateSoftwareRenderer(surface);

    if (swRender == NULL) {
        std::cout << "SDL Render Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetRenderDrawColor( swRender , border.r , border.g ,  border.b ,  border.a );
    //Clear the texture with the border colour
    SDL_RenderClear ( swRender );

/* GENERAL BUTTON RENDER  */

    //Create offset for the filler with the border
    area.x =  border_width;
    area.y =  border_width;
    area.w -= border_width*2;
    area.h -= border_width*2;

    //Render the filler
    SDL_SetRenderDrawColor( swRender , fg.r , fg.g ,  fg.b ,  fg.a );

    SDL_RenderFillRect(swRender , &area );

/* GENERAL BUTTON RENDER  */

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer , surface);

    if (texture == 0) {
        std::cout << "SDL Render Error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    //Delete render
    SDL_DestroyRenderer(swRender);

    //Free surface
    SDL_FreeSurface(surface);

    return texture;
}

} /* namespace ui */
