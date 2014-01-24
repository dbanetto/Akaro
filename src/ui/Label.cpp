/*
 * Label.cpp
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#include "Label.h"
#include <iostream>

namespace ui {

Label::Label() {
	this->font = nullptr;
	this->texture = nullptr;
	this->RENDER_TEXTURE = false;
	this->UPDATE_POSITION = false;
}

Label::Label(std::string label, TTF_Font* font , SDL_Point pos)
{
	this->font = font;
	this->text = label;
	this->texture = nullptr;

	//Set default foreground colour
	this->fg.r = 255;
	this->fg.g = 255;
	this->fg.b = 255;

	//Set flag to update the texture
	this->RENDER_TEXTURE = true;
	this->UPDATE_POSITION = true;

	this->pos.x = pos.x;
	this->pos.y = pos.y;

}

Label::~Label() {
	if (this->texture != nullptr) {
		SDL_DestroyTexture( this->texture );
	}
}

void Label::render (const Ldouble& delta , SDL_Renderer* renderer , etc::Camera& camera )
{
	//Check if the text needs to be rendered
	if (this->RENDER_TEXTURE) {
		//If the Label has a texture destroy it FOR SAFETY!
		if (this->texture != nullptr) {
			SDL_DestroyTexture(this->texture);
		}
		this->texture = generateLabelTexture( this->text , renderer , this->font , this->fg, &(this->area));
		this->RENDER_TEXTURE = false;
		this->UPDATE_POSITION = true;
	}

	SDL_Rect temp = this->area;
    if (this->adjust_camera)
    {
        temp = camera.subCamPos(this->area);
    }
	SDL_RenderCopy( renderer , this->texture , NULL , &(temp) );
}

void Label::update (const Ldouble& delta )
{
	//Update the Font
    if (this->UPDATE_POSITION)
    {
        this->pos.x = area.x;
        this->pos.y = area.y;
        this->UPDATE_POSITION = false;
    }
}

void Label::setText (std::string Text) {
	//No change in text save a render
	if (this->text == Text)
		return;

	this->text = Text;

	//Set flag to update the font

	//Flag prevents multiple edits in a frame
	//and only need to render once
	this->RENDER_TEXTURE = true;
}

SDL_Texture* generateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg , SDL_Rect* size )
{
	//Render the font
	SDL_Surface* sf = TTF_RenderText_Blended( font , text.c_str() , fg );

	//Return width and height of rendered text
	//Only if the rect is not null
	if (size != nullptr) {
      size->w = sf->w;
      size->h = sf->h;
	}

	//Convert the rendered font to a texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface ( renderer , sf );

	//Free the surface from the font rendering
	SDL_FreeSurface( sf );

	//return the texture pointer
	return tex;
}
SDL_Texture* generateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg ) {
  return generateLabelTexture (text , renderer , font , fg , nullptr);
}

void centerLabel (SDL_Rect area , Label* label)
{
  //Get the center of the area
  int area_center_x = area.x + area.w/2;
  int area_center_y = area.y + area.h/2;
  SDL_Rect lb = label->getRect();
  //Subtract half of the width and height of the label
  // So it is off setted to be the correct position
  area_center_x -= lb.w/2;
  area_center_y -= lb.h/2;

  //Set the label to the new position
  label->setPosition(area_center_x , area_center_y);
}

} /* namespace ui */
