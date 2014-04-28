/*
 * MapTile.h
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#ifndef MAPTILE_H_
#define MAPTILE_H_

#include "../graphics/Sprite.h"
#include <string>

namespace map
{

	class MapTile: public graphics::Sprite
	{
		public:
			MapTile();
			MapTile ( graphics::Texture* texture
					  , SDL_Point Position );
			MapTile ( graphics::Texture* texture
					  , SDL_Rect Position
					  , int SpriteMapIndex
					  , double Rotation
					  , SDL_Point CenterofRotation
					  , SDL_RendererFlip flip );

			virtual ~MapTile();

			void load( std::string config );
	};

} /* namespace map */

#endif /* MAPTILE_H_ */
