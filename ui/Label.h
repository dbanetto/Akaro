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

namespace ui {

class Label {



public:
	Label();
	Label(std::string label, TTF_Font* font , SDL_Point pos);
	virtual ~Label();

	void render (const double& delta , SDL_Renderer* renderer );
	void update (const double& delta );


	void setText (std::string text);
	void setPosition (SDL_Point pos);
	void setPosition (int x , int y);

	SDL_Rect getArea ();
	SDL_Point getPosition ();

private:
	SDL_Rect  clip;
	TTF_Font* font;
	SDL_Texture* texture;
	std::string text;
	SDL_Color fg;

	bool RENDER_TEXTURE;

};

//Other Label related Functions
SDL_Texture* GenerateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg , SDL_Rect* size );
SDL_Texture* GenerateLabelTexture ( std::string text , SDL_Renderer* renderer , TTF_Font* font , SDL_Color fg );
void centerLabel (SDL_Rect area , Label* label);

} /* namespace ui */

#endif /* LABEL_H_ */
