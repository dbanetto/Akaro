/*
 * Label.h
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#ifndef LABEL_H_
#define LABEL_H_

#if __GNUC__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_tff.h"
#endif

#include <string>
#include "../graphics/drawable.h"
#include "Font.h"

namespace ui
{

	class Label : public graphics::drawable
	{

		public:
			Label();
			Label( std::string label, Font* font , SDL_Point pos );
			virtual ~Label();

			void render ( const Ldouble& delta , SDL_Renderer* renderer , etc::Camera& camera );
			void update ( const Ldouble& delta );


			void setText ( std::string text );

			bool RENDER_TEXTURE;
			bool UPDATE_POSITION;
		private:
			Font* font;
			SDL_Texture* texture;
			std::string text;
			SDL_Color fg;

	};

//Other Label related Functions
	SDL_Texture* generateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg , SDL_Rect* size );
	SDL_Texture* generateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg );
	void centerLabel ( SDL_Rect area , Label* label );

} /* namespace ui */

#endif /* LABEL_H_ */
