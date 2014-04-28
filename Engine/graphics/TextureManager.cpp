/*
 * TextureManager.cpp
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#include "TextureManager.h"

namespace graphics
{

	TextureManager::TextureManager ()
	{
		this->renderer = nullptr;
	}

	TextureManager::TextureManager ( SDL_Renderer* renderer )
	{
		this->renderer = renderer;
	}

	TextureManager::~TextureManager ()
	{
		this->unload();
	}

	bool TextureManager::load ( std::string name , std::string file )
	{
		return this->load( file, name, 0, 0 );
	}

	bool TextureManager::load ( std::string name , std::string file , int columns , int rows )
	{
		this->textures[name] = Texture();
		Texture* temp = &( this->textures[name] );
		if ( temp->load ( this->renderer , file , columns , rows ) == true )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void TextureManager::unload()
	{
		for ( auto tex : this->textures )
		{
			SDL_DestroyTexture( tex.second.getTexture() );
		}
		this->textures.clear();

	}

	bool TextureManager::exists ( std::string name )
	{
		if ( this->textures.find( name ) == this->textures.end() )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Texture* TextureManager::getTexture ( std::string name )
	{
		if ( this->exists( name ) )
		{
			return &( this->textures[name] );
		}
		else
		{
			return nullptr;
		}

	}

} /* namespace graphics */