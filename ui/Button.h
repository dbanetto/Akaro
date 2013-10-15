/*
 * Button.h
 *
 *  Created on: 9/10/2013
 *      Author: drb
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include "Label.h"
#include "../graphics/drawable.h"

namespace ui {

class Button : public graphics::drawable {
public:

//Tydefs of Call back functions for the button
typedef void (*ButtonClickedCallBack)  (Button* btn);
typedef void (*ButtonUnclickedCallBack)(Button* btn);
typedef void (*ButtonHoverCallBack)    (Button* btn);
typedef void (*ButtonUnhoverCallBack)  (Button* btn);
// A struct will all the required callback functions
struct ButtonCallBacks {
    ButtonClickedCallBack button_clicked = nullptr;
    ButtonUnclickedCallBack button_unclicked = nullptr;
    ButtonHoverCallBack   button_hover   = nullptr;
    ButtonUnhoverCallBack button_unhover = nullptr;
};


	Button ();
	Button( SDL_Rect pos , SDL_Color fg, SDL_Color border , int border_width , ButtonCallBacks callbacks , Label label );
	virtual ~Button();

	void render (const double& delta , SDL_Renderer* renderer );
	void update (const double& delta );

    //Flags for updating rendered texture or position
    bool RENDER_TEXTURE;
    bool UPDATE_POSITION;
private:
	Label label;

	SDL_Texture* texture;

	SDL_Color fg;
	SDL_Color border;

	int border_width;
	ButtonCallBacks button_events;
};

//Util Functions for Button
SDL_Texture* generateButtonTexture ( SDL_Renderer* renderer , SDL_Color fg , SDL_Color border, int border_width , SDL_Rect area );

} /* namespace ui */

#endif /* BUTTON_H_ */
