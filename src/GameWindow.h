/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#pragma once

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

//Cross-Platform
#if __GNUC__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_net.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#endif

#include "content.h"
#include "graphics/TextureManager.h"
#include "etc/Camera.h"

//TODO : Support Multiple 'Game States'

/// <summary>
/// GameWindow Class to handle Rendering, Updating and events
/// </summary>
class GameWindow
{
	public:
		GameWindow(Content* content);
		virtual ~GameWindow();

		int init(const char* TITLE , SDL_Color BACKGROUND_COLOUR ,  int SDL_SCREEN_FLAGS );

		void start(void);
		int CURRENT_FPS;

		graphics::TextureManager* getTextures();
	protected:
		void render(const Ldouble& delta);
		void update(const Ldouble& delta);
		void event (SDL_Event e , const double& delta);

		void load();
		void unload();

		//util functions
		void screenshot();
	private:


		//Private variables
		SDL_Renderer* renderer;
		SDL_Window*   window;
		bool inited, quit;

		//Content and Graphics
		Content* content;
		etc::Camera camera;
		graphics::TextureManager textures;

		//GAME TIME
		double GAMETIME_MULTIPLIER;
		int FRAME_LIMIT;
		bool CAP_FRAMES;

		//background colour
		SDL_Color background;

		//Battery
		bool has_battery;
		//Measured in seconds
		double last_battery_check;
};

#endif
