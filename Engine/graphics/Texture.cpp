/*
 * Texture.cpp
 *
 *  Created on: 14/11/2013
 *      Author: drb
 */

#include "Texture.h"

#if __GNUC__
#include <SDL2/SDL_image.h>
#else
#include "SDL_image.h"
#endif

#include <iostream>

namespace graphics
{

	Texture::Texture ()
	{
		this->texture = nullptr;
		this->is_loaded = false;
		this->rows = 0;
		this->columns = 0;
	}

	Texture::Texture (SDL_Renderer* renderer,std::string file)
	{
		this->texture = nullptr;
		this->is_loaded = false;
		this->rows = 0;
		this->columns = 0;
		this->load(renderer,file);
	}

	Texture::Texture (const Texture& tex)
	{
		this->is_loaded = false;
		this->texture = nullptr;
		this->rows = 0;
		this->columns = 0;
	}

	Texture::~Texture ()
	{

		if (this->texture != nullptr)
		{
			SDL_DestroyTexture(this->texture);
		}
	}

	bool Texture::load (SDL_Renderer* renderer, std::string file)
	{
		return this->load(renderer,file,0,0);
	}

	bool Texture::load (SDL_Renderer* renderer, std::string file, int columns, int rows)
	{
		SDL_Surface* surf = IMG_Load(file.c_str());
		if (surf == nullptr)
		{
			std::cout << file << " failed to load. " << SDL_GetError() << std::endl;
			return false;
		}

		//Can only create if both columns
		if (columns > 0 && rows > 0)
		{
			//Create rects
			this->sprite_map.clear();
			this->sprite_map.reserve(columns*rows);
			int width = surf->w / columns;
			int hieght = surf->h / rows;
			this->columns = columns;
			this->rows = rows;
			for (int y = 0; y < columns; y++ )
			{
				for (int x = 0; x < rows; x++ )
				{
					SDL_Rect map;
					map.x = x*width;
					map.y = y*hieght;
					map.w = width;
					map.h = hieght;

					this->sprite_map.push_back(map);
				}
			}
		}
		else
		{
			this->sprite_map.clear();
			this->sprite_map.reserve(1);
			SDL_Rect map;
			map.x = 0;
			map.y = 0;
			map.w = surf->w;
			map.h = surf->h;
			this->sprite_map.push_back(map);
		}

		this->texture = SDL_CreateTextureFromSurface ( renderer, surf );

		if (this->texture == nullptr)
		{
			std::cout << file << " failed to convert to texture. " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_FreeSurface(surf);
		this->is_loaded = true;
		return true;
	}

	bool Texture::load (SDL_Renderer* renderer,std::string file , std::vector<SDL_Rect> sprite_map)
	{
		if (this->load(renderer,file,0,0) == true)
		{
			this->sprite_map = sprite_map;
			return true;
		}
		else
		{
			return false;
		}
	}

	SDL_Texture* Texture::getTexture()
	{
		return this->texture;
	}

	SDL_Rect* Texture::getSprite(int column, int row)
	{
		return &(this->sprite_map[column*rows + row]);
	}

	SDL_Rect* Texture::getSprite(int index)
	{
		return &(this->sprite_map[index]);
	}

} /* namespace graphics */
