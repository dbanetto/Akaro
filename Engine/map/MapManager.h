#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "Map.h"

#include <string>
#include <map>

namespace map
{
	class MapManager
	{
		public:
			MapManager();
			MapManager(graphics::TextureManager* Textures);
			virtual ~MapManager();

			bool exists( std::string name );
			bool load( std::string name, std::string mapPath );
			Map* get( std::string name );

			void unload ( std::string name );
			void unloadAll();
		protected:
		private:
			std::map<std::string, Map*> maps;
			graphics::TextureManager* textures;
	};

}
#endif // MAPMANAGER_H
