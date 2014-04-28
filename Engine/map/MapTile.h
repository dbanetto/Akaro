/*
 * MapTile.h
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#ifndef MAPTILE_H_
#define MAPTILE_H_

#include "../graphics/Sprite.h"
#include "../graphics/TextureManager.h"

#include <string>

namespace map
{

	class MapTile: public graphics::Sprite
	{
		public:
			MapTile();
			MapTile ( graphics::TextureManager* textures
					  , std::string textureName
					  , SDL_Point Position );
			MapTile ( graphics::TextureManager* textures
					  , std::string textureName
					  , SDL_Rect Position
					  , int SpriteMapIndex
					  , double Rotation
					  , SDL_Point CenterofRotation
					  , SDL_RendererFlip flip );

			virtual ~MapTile();

			void render(const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera );
		private:
			std::string texture_name;
	};

} /* namespace map */

#endif /* MAPTILE_H_ */
