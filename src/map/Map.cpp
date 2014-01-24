/*
 * Map.cpp
 *
 *  Created on: 24/01/2014
 *      Author: drb
 */

#include "Map.h"
#include <fstream>


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
	//std::fstream fs;
	//fs.open(file.c_str());
	for (int x = 0; x < 500; x++) {
		for (int y = 0; y < 500; y++) {
			MapTile* tile;
			SDL_Rect pos;
			pos.x = x * 32;
			pos.y = y * 32;
			pos.h = 32;
			pos.w = 32;

			SDL_Point cor;
			cor.x = 16;
			cor.y = 16;

			tile = new MapTile( this->textures->getTexture("grass") , pos, (x % 4 + y % 2) % 4 , 0 , cor , (SDL_RendererFlip)(y % 2));
			tile->setAdjustCamera(true);

			this->maptiles.push_back(tile);
			this->map.insert(tile);
		}
	}

	//fs.close();
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
