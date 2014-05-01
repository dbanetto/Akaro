/*
 * Map.cpp
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#include "Map.h"
#include <fstream>
#include <iostream>
#include "../etc/string.h"
#include "../io/file.h"

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace map
{

	Map::Map()
	{
		// TODO Auto-generated constructor stub
		this->textures = nullptr;
		this->inited = false;
	}

	Map::~Map()
	{
		// TODO Auto-generated destructor stub
		unload();
	}

	Map::Map( graphics::TextureManager* textures )
	{
		this->init( textures );
	}

	bool Map::init ( graphics::TextureManager* textures )
	{
		this->textures = textures;
		this->map = etc::AreaMap();

		this->inited = true;
		return this->inited;
	}

	/**
	 * @brief Load Map file
	 * @parm file File path to map
	 */
	bool Map::loadMap( std::string file , map::TileTypeManager* tiletypes )
	{
		if ( !IO::fileExists( file ) )
		{
			std::cout << "ERROR " << file << " does not exits!" << std::endl;
			return false;
		}

		std::fstream fs;
		fs.open( file.c_str() );

		while ( ! fs.eof() )
		{
			std::string line;
			std::getline( fs , line );
			line = etc::trim( line );

			//Skip empty lines
			if ( line == "" )
				continue;

			// # are comments
			if ( etc::startswith( line , "#" ) )
				continue;

			auto seg = etc::split( line, "," );

			SDL_Rect pt;
			std::string tex;
			int tex_index = 0;
			SDL_RendererFlip flip;


			//Texture name
			tex = seg[2];

			auto type =  tiletypes->get(tex);

			if (type == nullptr)
			{
				std::cout << "Error " << tex << " is not a defined Tile Type" << std::endl;
				continue;
			}

			//Texture Map index
			tex_index = atoi( seg[3].c_str() );

			//Texture flip
			flip = ( SDL_RendererFlip )atoi( seg[4].c_str() );

			//Position
			//X
			pt.x = atoi( seg[0].c_str() );

			//Y
			pt.y = atoi( seg[1].c_str() );

			SDL_Rect* size = this->textures->getTexture( tex )->getSprite( tex_index );
			pt.w = size->w;
			pt.h = size->h;



			MapTile* tile;
			SDL_Point cor; //center of rotation
			cor.x = pt.w / 2;
			cor.y = pt.h / 2;


			tile = new MapTile( this->textures
								, type
								, pt
								, tex_index
								, 0.0
								, cor
								, flip );
			tile->setAdjustCamera( true );

			this->maptiles.push_back( tile );
			this->map.insert( tile );
#ifdef LOADING_VERBOSE
			std::cout << "Loaded " << line << std::endl;
#endif
		}

		fs.close();
		return true;
	}

	void Map::unloadMap()
	{
		for ( auto tile : this->maptiles )
		{
			delete tile;
		}
		this->maptiles.clear();
	}

	void Map::unload()
	{
		unloadMap();
	}

	void Map::render ( const Ldouble& delta, graphics::TextureManager* textures , etc::Camera& camera )
	{
		std::vector<graphics::drawable*> tiles;
		this->map.getSpritesFromArea( camera.getViewport() , &tiles );
		for ( auto t : tiles )
		{
			MapTile* tile = (MapTile*)t;
			tile->render( delta , textures , camera );
		}
	}
	void Map::update ( const Ldouble& delta )
	{

	}

	bool Map::isLoaded()
	{
		return this->inited;
	}

	etc::AreaMap* Map::getAreaMap()
	{
		return &(this->map);
	}

} /* namespace map */
