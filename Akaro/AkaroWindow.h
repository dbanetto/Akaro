/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#pragma once

#ifndef AKAROWINDOW_H_
#define AKAROWINDOW_H_

#include "Engine/GameWindow.h"

class AkaroWindow : GameWindow
{
	public:
		AkaroWindow(Content* content);
		virtual ~AkaroWindow();

		int init(const char* TITLE , SDL_Color BACKGROUND_COLOUR ,  int SDL_SCREEN_FLAGS );

		void start(void);
		int CURRENT_FPS;

		graphics::TextureManager* getTextures();

		void render(const Ldouble& delta);
		void update(const Ldouble& delta);
		void event (SDL_Event e , const double& delta);

		void load();
		void unload();

	protected:
	private:
};

#endif
