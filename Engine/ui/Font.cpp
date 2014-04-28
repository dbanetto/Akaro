#include "Font.h"

#include "../io/file.h"

using namespace ui;

Font::Font()
{
	//ctor
	this->font = nullptr;
	this->loaded = false;
}

Font::~Font()
{
	//dtor
	unload();
}

bool Font::load( std::string fontPath )
{
	if ( IO::fileExists( fontPath ) )
	{
		this->font = TTF_OpenFont( fontPath.c_str() , 11 );
		this->loaded = ( this->font != 0 );
		return this->loaded;
	}
	else
	{
		return false;
	}
}

void Font::unload()
{
	if ( this->loaded )
	{
		TTF_CloseFont( this->font );
		this->font = nullptr;
	}
	this->loaded = false;
}

bool Font::isLoaded()
{
	return this->loaded;
}

TTF_Font* Font::getFont()
{
	return this->font;
}
