#include "MapManager.h"

#include <iostream>

using namespace map;

MapManager::MapManager()
{
	this->textures = nullptr;
}

MapManager::~MapManager()
{

}

void MapManager::init (graphics::TextureManager* Textures)
{
	this->textures = Textures;
}

void MapManager::unloadAll()
{
	for ( auto& obj : this->maps )
	{
		if ( obj.second->isLoaded() )
		{
			obj.second->unload();
		}
		delete obj.second;
	}
	this->maps.clear();
}

void MapManager::unload ( std::string name )
{
	if ( this->exists( name ) )
	{
		this->maps[name]->unload();
		delete this->maps[name];
		this->maps.erase( name );
	}
}

Map* MapManager::get( std::string name )
{
	if ( this->exists( name ) )
	{
		return this->maps[name];
	}
}

bool MapManager::exists( std::string name )
{
	return ( this->maps.find( name ) != this->maps.end() && textures != nullptr);
}

bool MapManager::load ( std::string name, std::string mapPath )
{
	if (textures == nullptr)
	{
		std::cout << "WARNING The font " << name << " (" << mapPath << ") failed to load." << std::endl;
		std::cout << "Textures are not set" << std::endl;
		return false;
	}

	if ( !this->exists( name ) )
	{
		Map* mp = new Map(textures);
		bool out = mp->loadMap( mapPath);

		if ( out )
		{
			this->maps[name] = mp;
		}

		return out;
	}
	else
	{
		std::cout << "WARNING The Map " << name << " (" << mapPath << ") failed to load." << std::endl;
		std::cout << name << " already exists" << std::endl;
		return false;
	}
}
