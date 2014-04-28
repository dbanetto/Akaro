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

	MapTile::MapTile ( graphics::Texture* texture , SDL_Rect Position, int SpriteMapIndex , double Rotation , SDL_Point CenterofRotation, SDL_RendererFlip flip )
		: graphics::Sprite( texture , Position , SpriteMapIndex , Rotation, CenterofRotation , flip )
	{

	}

	MapTile::~MapTile()
	{
		// TODO Auto-generated destructor stub
	}
	/**
	 * @brief Load from string config
	 */
	void MapTile::load( std::string config )
	{
		// Example x:y:::
	}

} /* namespace map */
