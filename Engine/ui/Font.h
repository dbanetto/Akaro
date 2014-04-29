#ifndef FONT_H
#define FONT_H

#ifdef __GNUC__
#include <SDL2/SDL_ttf.h>
#else
#include "SDL_ttf.h"
#endif

#include <string>
namespace ui
{
	enum FontStyle  {
		FontStyle_Normal = TTF_STYLE_NORMAL,
		FontStyle_Bold = TTF_STYLE_BOLD,
		FontStyle_Italic = TTF_STYLE_ITALIC,
		FontStyle_Underline = TTF_STYLE_UNDERLINE,

		FontStyle_Bold_Italic = (FontStyle_Bold | FontStyle_Italic)
#ifdef FONT_DANGEROUS_STYLES
		,FontStyle_Bold_UnderLine = (FontStyle_Bold | FontStyle_Underline),
		FontStyle_Italic_UnderLine = (FontStyle_Italic | FontStyle_Underline),
		FontStyle_Bold_Italic_UnderLine = (FontStyle_Bold | FontStyle_Italic | FontStyle_Underline)
#endif
	};

	enum FontHinting {
		FontHiniting_Normal = 0,
		FontHiniting_Light  = 1,
		FontHiniting_Mono   = 2,
		FontHiniting_None   = 3
	};

	class Font
	{
		public:
			/** Default constructor */
			Font();
			/** Default destructor */
			virtual ~Font();

			bool load( std::string fontPath , int ptsize);
			void unload();
			TTF_Font* getFont();
			bool isLoaded();

			FontStyle getFontStyle();
			FontStyle setFontStyle(FontStyle style);

			FontHinting getFontHinting();
			FontHinting setFontHinting(FontHinting hint);

		protected:
		private:
			TTF_Font* font;
			FontStyle fontstyle;
			bool loaded;
	};

}
#endif // FONT_H
