/*
 * Map.cpp
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#include "Map.h"
#include <fstream>
#include "../etc/string.h"

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace map {

Map::Map() {
	// TODO Auto-generated constructor stub
	this->textures = nullptr;
	this->inited = false;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
	unload();
}

Map::Map(graphics::TextureManager* textures)
{
	this->inited = false;
	this->textures = nullptr;
	this->init(textures);
}

bool Map::init (graphics::TextureManager* textures)
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
void Map::loadMap(std::string file)
{
	std::fstream fs;
	fs.open(file.c_str());
	std::string line;
	while ( ! fs.eof() )
	{
		std::getline( fs , line );
		// # are comments
		if (etc::startswith( line , "#" ) )
			continue;

		auto seg = etc::split(line, ",");
		SDL_Rect pt;
		std::string tex;
		int tex_index = 0;
		SDL_RendererFlip flip;


		//Texture name
		tex = seg[2];

		//Texture Map index
		tex_index = atoi( seg[3].c_str() );

		//Texture flip
		flip = (SDL_RendererFlip)atoi( seg[4].c_str() );

		//Position
		//X
		pt.x = atoi( seg[0].c_str() );

		//Y
		pt.y = atoi( seg[1].c_str() );

		SDL_Rect* size = this->textures->getTexture(tex)->getSprite(tex_index);
		pt.w = size->w;
		pt.h = size->h;



		MapTile* tile;
		SDL_Point cor; //center of rotation
		cor.x = pt.w/2; cor.y = pt.h/2;

		tile = new MapTile( this->textures->getTexture(tex)
				, pt
				, tex_index
				, 0.0
				, cor
				, flip );
		tile->setAdjustCamera(true);
		this->maptiles.push_back(tile);
		this->map.insert(tile);
	}

	fs.close();
}

void Map::unloadMap()
{
	for (auto tile : this->maptiles)
	{
		delete tile;
	}
	this->maptiles.clear();
}

void Map::unload()
{
	unloadMap();
}

void Map::render (const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera)
{
	auto tiles = this->map.getSpritesFromArea(camera.getViewport());
	for (auto tile : tiles) {
		tile->render(delta , renderer , camera);
	}
}
void Map::update (const Ldouble& delta)
{

}

} /* namespace map */
