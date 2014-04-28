/*
 * MapTile.cpp
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#include "MapTile.h"

namespace map
{

	MapTile::MapTile()
	{
		// TODO Auto-generated constructor stub

	}

	MapTile::MapTile ( graphics::TextureManager* textures
					  , std::string textureName
					  , SDL_Point Position ) :
			graphics::Sprite(textures->getTexture(textureName) , Position)
	  {
		this->texture_name = textureName;
	  }
	MapTile::MapTile ( graphics::TextureManager* textures
					  , std::string textureName
					  , SDL_Rect Position
					  , int SpriteMapIndex
					  , double Rotation
					  , SDL_Point CenterofRotation
					  , SDL_RendererFlip flip ) :
		graphics::Sprite(textures->getTexture(textureName), Position, SpriteMapIndex, Rotation, CenterofRotation, flip)
	  {
		this->texture_name = textureName;
	  }



	MapTile::~MapTile()
	{
		// TODO Auto-generated destructor stub
	}

	void MapTile::render(const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera )
	{
		this->setTexture( textures->getTexture( this->texture_name ) );
		Sprite::render(delta , textures->getRenderer(), camera);
	}

} /* namespace map */
