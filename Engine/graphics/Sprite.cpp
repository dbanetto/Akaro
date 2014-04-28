/*
 * Sprite.cpp
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#include "Sprite.h"

#include <iostream>

namespace graphics
{

	Sprite::Sprite ()
	{
		this->tex = nullptr;
		this->sprite_map_index = 0;
		this->rot = 0;
		this->flip = SDL_FLIP_NONE;
	}

	Sprite::Sprite ( Texture* texture , SDL_Point Position )
	{
		this->area = SDL_Rect();
		this->area.w = texture->getSprite( 0 )->w;
		this->area.h = texture->getSprite( 0 )->h;
		this->area.x = Position.x;
		this->area.y = Position.y;

		this->pos.x = Position.x;
		this->pos.y = Position.y;

		this->tex = texture;

		this->sprite_map_index = 0;
		this->rot = 0;
		this->flip = SDL_FLIP_NONE;

		this->cor = SDL_Point();
		this->cor.x = 0;
		this->cor.y = 0;
	}

	Sprite::Sprite ( Texture* texture , SDL_Rect Position, int SpriteMapIndex , double Rotation , SDL_Point CenterofRotation, SDL_RendererFlip flip )
	{
		this->area = Position;
		this->pos.x = this->area.x;
		this->pos.y = this->area.y;
		this->tex = texture;
		this->sprite_map_index = SpriteMapIndex;
		this->rot = Rotation;
		this->cor = CenterofRotation;
		this->flip = flip;
	}

	Sprite::~Sprite ()
	{
	}

	void Sprite::render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera )
	{
		SDL_Rect temp = this->area;
		if ( this->adjust_camera )
		{
			temp = camera.subCamPos( this->area );
		}
		SDL_Texture* texture = this->tex->getTexture();
		SDL_RenderCopyEx( renderer, texture, this->tex->getSprite( this->sprite_map_index ), &( temp ), this->rot, &( this->cor ), this->flip );
	}

	void Sprite::update ( const Ldouble& delta )
	{

	}

	//Getters and Setters
	/**
	 * @brief Set Texture for sprite
	 */
	void Sprite::setTexture ( Texture* texture )
	{
		this->tex = texture;
	}
	/**
	 * @brief Set Render Flip mode
	 */
	void Sprite::setFlip ( SDL_RendererFlip flip )
	{
		this->flip = flip;
	}
	/**
	 * @brief Set centre of rotation, in relation to sprite's top left (0,0)
	 */
	void Sprite::setCenterOfRotation ( SDL_Point pt )
	{
		this->cor = pt;
	}
	/**
	 * @brief Set Sprite's rotation, in rads
	 */
	void Sprite::setRotation ( double rot )
	{
		this->rot = rot;
	}
	/**
	 * @brief Set Sprite's texture index, for its sprite map.
	 */
	void Sprite::setSpriteMapIndex ( int sprite_map_index )
	{
		this->sprite_map_index = sprite_map_index;
	}

	Texture* Sprite::getTexture()
	{
		return this->tex;
	}
	SDL_RendererFlip Sprite::getFlip()
	{
		return this->flip;
	}
	SDL_Point Sprite::getCenterOfRotation()
	{
		return this->cor;
	}
	double Sprite::getRotation()
	{
		return this->rot;
	}
	int Sprite::getSpriteMapIndex ()
	{
		return this->sprite_map_index;
	}

} /* namespace graphics */
