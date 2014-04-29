#include "FontManager.h"

#include <iostream>

using namespace ui;

FontManager::FontManager()
{

}

FontManager::~FontManager()
{
	this->fonts.clear();

}

void FontManager::unloadAll ()
{
	this->fonts.clear();
	for (auto& fts : this->created_fonts)
	{
		for (auto& ft : fts.second)
		{
			if (ft->isLoaded())
				ft->unload();

			delete ft;
		}
		fts.second.clear();
	}
	this->created_fonts.clear();
}
/**
  * @param name Name of the font to be unloaded
  * @note Frees all allocated Fonts under 'name'
  * This can lead to objects pointing to nothing
  * ONLY do this if you are sure ALL of the references to
  * the allocated fonts are gone
  */
void FontManager::unload ( std::string name )
{
	if ( this->exists( name ) )
	{
		this->fonts.erase( name );

		auto fts = this->created_fonts[name];
		for (auto& ft : fts)
		{
			if (ft->isLoaded())
				ft->unload();

			delete ft;

		}
		fts.clear();
		this->created_fonts.erase(name);
	}
}

Font* FontManager::get( std::string name , int size)
{
	if ( this->exists( name ) )
	{
		Font* out = new Font();
		out->load( this->fonts[name] , size );
		created_fonts[name].push_back(out);
		return out;
	}
}

bool FontManager::exists( std::string name )
{
	return ( this->fonts.find( name ) != this->fonts.end() );
}

bool FontManager::load ( std::string name, std::string fontPath )
{
	if ( !this->exists( name ) )
	{
		this->fonts[name] = fontPath;
		return true;
	}
	else
	{
		std::cout << "WARNING The font " << name << " (" << fontPath << ") failed to load." << std::endl;
		std::cout << name << " already exists" << std::endl;
		return false;
	}
}
