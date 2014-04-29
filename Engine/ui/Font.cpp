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

bool Font::load( std::string fontPath , int ptsize)
{
	if ( IO::fileExists( fontPath ) )
	{
		this->font = TTF_OpenFont( fontPath.c_str() , ptsize );
		this->loaded = ( this->font != 0 );
		if (this->loaded)
			this->fontstyle = (FontStyle)(TTF_GetFontStyle(this->font));
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

FontStyle Font::getFontStyle()
{
	return this->fontstyle;
}

/**
  * @param FontStyle style to be applied
  * @return The FontStyle that the is Font using
  * @note Only applies if there is a change in style
  */
FontStyle Font::setFontStyle(FontStyle style)
{
	if (style != this->fontstyle)
	{
        this->fontstyle = style;
        TTF_SetFontStyle(this->font , this->fontstyle);
	}
	return this->fontstyle;
}

FontHinting Font::getFontHinting()
{
	return (FontHinting)(TTF_GetFontHinting(this->font));
}

FontHinting Font::setFontHinting(FontHinting hint)
{
	if (TTF_GetFontHinting(this->font) != (int)hint)
	{
		TTF_SetFontHinting(this->font , (int)hint);
	}
	return (FontHinting)TTF_GetFontHinting(this->font);
}
