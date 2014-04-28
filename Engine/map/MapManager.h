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
			virtual ~MapManager();
			void init (graphics::TextureManager* Textures);

			bool exists( std::string name );
			bool load( std::string name, std::string mapPath );
			Map* get( std::string name );

			bool setCurrentMap(std::string name);
			std::string getCurrentMapName();

			void unload ( std::string name );
			void unloadAll();
		protected:
		private:
			std::map<std::string, Map*> maps;
			graphics::TextureManager* textures;
			std::string current_map;
	};

}
#endif // MAPMANAGER_H
