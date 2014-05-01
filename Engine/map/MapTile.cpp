/*
 * MapTile.cpp
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#include "MapTile.h"

namespace map
{

	MapTile::MapTile() :
			graphics::Sprite()
	{
		// TODO Auto-generated constructor stub
		this->tiletype = nullptr;
	}

	MapTile::MapTile ( graphics::TextureManager* textures
					, TileType* tiletype
					, SDL_Point Position ) :
			graphics::Sprite(textures->getTexture(tiletype->texture_name) , Position)
	{
		this->tiletype = tiletype;
	}
	MapTile::MapTile ( graphics::TextureManager* textures
					, TileType* tiletype
					, SDL_Rect Position
					, int SpriteMapIndex
					, double Rotation
					, SDL_Point CenterofRotation
					, SDL_RendererFlip flip ) :
		graphics::Sprite(textures->getTexture(tiletype->texture_name), Position, SpriteMapIndex, Rotation, CenterofRotation, flip)
	{
		this->tiletype = tiletype;
	}



	MapTile::~MapTile()
	{
		// TODO Auto-generated destructor stub
	}

	void MapTile::render(const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera )
	{
		this->setTexture( textures->getTexture( this->tiletype->texture_name ) );
		Sprite::render(delta , textures->getRenderer(), camera);
	}

	MapTile::TileType* MapTile::getTileType()
	{
		return this->tiletype;
	}

} /* namespace map */
