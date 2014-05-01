#include "TileTypeManager.h"

using namespace map;

TileTypeManager::TileTypeManager()
{
	//ctor
}

TileTypeManager::~TileTypeManager()
{
	//dtor
}

void TileTypeManager::unloadAll()
{
	for ( auto& obj : this->types )
	{
		delete obj.second;
	}
	this->types.clear();
}

bool TileTypeManager::exists( std::string name )
{
	return ( this->types.find( name ) != this->types.end() );
}

bool TileTypeManager::add ( std::string name , MapTile::TileType* type )
{
	if (!this->exists(name))
	{
		this->types[name] = type;
		return true;
	}
	return false;
}

MapTile::TileType* TileTypeManager::get ( std::string name )
{
	if (this->exists(name))
	{
		return (this->types[name]);
	}
	return nullptr;
}
