/*
 * TextureManager.cpp
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#include "TextureManager.h"
#include "../io/file.h"
#include "../etc/string.h"
#include <iostream>
#include <fstream>

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
		if (!this->exists(name)) {
			this->textures[name] = Texture();
			Texture* temp = &( this->textures[name] );
			if ( temp->load ( this->renderer , file , columns , rows ) == true )
			{
				return true;
			}
		}
		return false;
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

	bool TextureManager::loadList (std::string file)
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

			/*
			 * Example of format :
			 * grass,data/textures/grass.png,2,2
			*/
			if (seg.size() != 4)
				continue;

			std::string name;
			std::string path;
			int col, row;


			//Texture name
			name = seg[0];

			//Texture path
			path = seg[1];

			//Sprite Sheet
			//Columns
			col = atoi( seg[2].c_str() );

			//Rows
			row = atoi( seg[3].c_str() );

			this->load(name , path , col , row);
		}

		fs.close();
		return true;
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

	SDL_Renderer* TextureManager::getRenderer()
	{
		return this->renderer;
	}

} /* namespace graphics */
