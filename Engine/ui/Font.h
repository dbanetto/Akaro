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
	class Font
	{
		public:
			/** Default constructor */
			Font();
			/** Default destructor */
			virtual ~Font();

			bool load( std::string fontPath );
			void unload();
			TTF_Font* getFont();
			bool isLoaded();
		protected:
		private:
			TTF_Font* font;
			bool loaded;
	};

}
#endif // FONT_H
