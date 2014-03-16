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

#include "../graphics/drawable.h"
#include "Label.h"

namespace ui
{

	class Button : public graphics::drawable
	{
		public:

//Tydefs of Call back functions for the button
			/**
			 * @brief Call back function for when the mouse clicks on the button
			 * @param btn Button that is calling back
			 */
			typedef void (*ButtonClickedCallBack)  (Button* btn);
			/**
			 * @brief Call back function for when the mouse stops clicking on the button
			 * @param btn Button that is calling back
			 */
			typedef void (*ButtonUnclickedCallBack)(Button* btn);
			/**
			 * @brief Call back function for when the mouse starts to hover over the button
			 * @param btn Button that is calling back
			 */
			typedef void (*ButtonHoverCallBack)    (Button* btn);
			/**
			 * @brief Call back function for when the mouse stops hovering over the button
			 * @param btn Button that is calling back
			 */
			typedef void (*ButtonUnhoverCallBack)  (Button* btn);

// A struct will all the required callback functions
			/**
			 * @brief A collection of Button Callback functions
			 */
			struct ButtonCallBacks
			{
				/**
				 * @see ButtonClickedCallBack
				 */
				ButtonClickedCallBack button_clicked = nullptr;
				/**
				 * @see ButtonUnclickedCallBack
				 */
				ButtonUnclickedCallBack button_unclicked = nullptr;
				/**
				 * @see ButtonHoverCallBack
				 */
				ButtonHoverCallBack   button_hover   = nullptr;
				/**
				 * @see ButtonUnhoverCallBack
				 */
				ButtonUnhoverCallBack button_unhover = nullptr;
			};


			Button ();
			Button( SDL_Rect pos , SDL_Color fg, SDL_Color border , int border_width , ButtonCallBacks callbacks , ui::Label label );
			virtual ~Button();

			void render (const Ldouble& delta , SDL_Renderer* renderer , etc::Camera& camera );
			void update (const Ldouble& delta );

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
