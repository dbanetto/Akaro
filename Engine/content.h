#ifndef CONTENT_H
#define CONTENT_H

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

#include "ui/Label.h"
#include "ui/Button.h"
#include "io/Settings.h"
#include "etc/battery.h"

#include "input/InputManager.h"
#include "states/GameStateManager.h"
#include "audio/AudioManager.h"
#include "map/MapManager.h"
#include "ui/FontManager.h"
#include "graphics/TextureManager.h"

class Content
{
	public:
		Content();
		virtual ~Content();

		int init();
		void load( SDL_Renderer* renderer );
		void unload();

		//Getters
		IO::Settings* Settings();
		input::InputManager* Input();
		audio::AudioManager* Audio();
		GameStateManager* Gamestate();
		ui::FontManager* Fonts();
		map::MapManager* Maps();
		graphics::TextureManager* Textures();
	protected:
	private:

		//Settings and Content managers
		IO::Settings settings;
		input::InputManager input;
		audio::AudioManager audio;
		ui::FontManager fonts;
		map::MapManager maps;
		GameStateManager gamestate;
		graphics::TextureManager textures;
};

#endif // CONTENT_H
