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
	// TODO Auto-generated constructor stub
	this->font = nullptr;
	this->texture = nullptr;
	this->RENDER_TEXT = false;
}

Label::Label(std::string label, TTF_Font* font)
{
	this->font = font;
	this->text = label;
	this->texture = nullptr;

	//Set default foreground colour
	this->fg.r = 255;
	this->fg.g = 255;
	this->fg.b = 255;

	//Set flag to update the texture
	this->RENDER_TEXT = true;

	this->clip.x = 0;
	this->clip.y = 0;

}

Label::~Label() {
	if (this->texture != nullptr) {
		SDL_DestroyTexture( this->texture );
	}
}

void Label::render (const double& delta , SDL_Renderer* renderer )
{
	//Check if the text needs to be rendered
	if (this->RENDER_TEXT) {
		//If the Label has a texture destroy it FOR SAFETY!
		if (this->texture != nullptr) {
			SDL_DestroyTexture(this->texture);
		}
		this->texture = GenerateTextTexture( this->text , renderer , this->font , this->fg, &(this->clip));
		this->RENDER_TEXT = false;
	}

	SDL_RenderCopy( renderer , this->texture , NULL , &(this->clip) );
}

void Label::update (const double& delta )
{
	//Update the Font
}

void Label::setText (std::string Text) {
	//No change in text save a render
	if (this->text == Text)
		return;

	this->text = Text;

	//Set flag to update the font

	//Flag prevents multiple edits in a frame
	//and only need to render once
	this->RENDER_TEXT = true;
}

void Label::setPosition (SDL_Point pos) {
	this->clip.x = pos.x;
	this->clip.y = pos.y;
}
void Label::setPosition (int x , int y) {
	this->clip.x = x;
	this->clip.y = y;
}

SDL_Texture* GenerateTextTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg , SDL_Rect* size )
{
	//Render the font
	SDL_Surface* sf = TTF_RenderText_Blended( font , text.c_str() , fg );

	//Return width and height of rendered text
	size->w = sf->w;
	size->h = sf->h;

	//Convert the rendered font to a texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface ( renderer , sf );

	//Free the surface from the font rendering
	SDL_FreeSurface( sf );

	//return the texture pointer
	return tex;
}

} /* namespace ui */
