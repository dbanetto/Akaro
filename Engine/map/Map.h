/*
 * Map.h
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#ifndef MAP_H_
#define MAP_H_

#include "../etc/AreaMap.h"
#include "MapTile.h"
#include <string>
#include <vector>
#include "../graphics/TextureManager.h"
#include "TileTypeManager.h"

namespace map
{

	class Map
	{
		public:
			Map();
			Map( graphics::TextureManager* textures );
			virtual ~Map();

			bool init ( graphics::TextureManager* textures );

			virtual void render ( const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera );
			virtual void update ( const Ldouble& delta );

			etc::AreaMap* getAreaMap();

			bool isLoaded();
			bool loadMap( std::string file , map::TileTypeManager* tiletypes );
			void unloadMap();
			void unload();
		private:
			etc::AreaMap map;
			std::vector<MapTile*> maptiles;
			graphics::TextureManager* textures;

			bool inited;
	};

} /* namespace map */

#endif /* MAP_H_ */
