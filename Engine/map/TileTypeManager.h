#ifndef TILETYPEMANAGER_H
#define TILETYPEMANAGER_H

#include "MapTile.h"

#include <map>
namespace map
{

	class TileTypeManager
	{
		public:
			TileTypeManager();
			virtual ~TileTypeManager();

			bool exists( std::string name );
			bool add ( std::string name , map::MapTile::TileType* type );
			map::MapTile::TileType* get ( std::string name );

			void unloadAll();
		protected:
		private:
			std::map<std::string , map::MapTile::TileType* > types;
	};

}
#endif // TILETYPEMANAGER_H
