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


	class MapTile : public graphics::Sprite
	{
		public:
			//Tile Events/Callbacks
			typedef void ( *TileOnTouch )( MapTile* maptile, graphics::Sprite* );
			typedef void ( *TileOnUpdate )(MapTile* maptile, Ldouble& );
			struct TileType
			{
				std::string name = "";
				std::string texture_name = "";

				bool collidable = false;

				TileOnTouch onTouch = nullptr;
				TileOnUpdate update = nullptr;
			};



			MapTile();
			MapTile ( graphics::TextureManager* textures
					  , TileType* tiletype
					  , SDL_Point Position );
			MapTile ( graphics::TextureManager* textures
					  , TileType* tiletype
					  , SDL_Rect Position
					  , int SpriteMapIndex
					  , double Rotation
					  , SDL_Point CenterofRotation
					  , SDL_RendererFlip flip );

			virtual ~MapTile();
			TileType* getTileType();
			void render(const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera );
		private:
			TileType* tiletype;

	};

} /* namespace map */

#endif /* MAPTILE_H_ */
