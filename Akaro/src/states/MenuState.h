/*
 * MenuState.h
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "Engine/src/states/GameState.h"
#include "Engine/src/states/GameStateManager.h"
#include "Engine/src/GameWindow.h"
#include "Engine/src/graphics/Sprite.h"
#include "Engine/src/map/Map.h"

class MenuState : public GameState
{
	public:
		MenuState(GameStateManager* Manager, GameWindow* gamewindow , Content* content);
		virtual
		~MenuState();

		//Each frame
		void render (const Ldouble& delta, SDL_Renderer* renderer , etc::Camera &camera);
		void update (const Ldouble& delta);
		void event (SDL_Event e , const Ldouble& delta);

		//Inital un/Load Assests
		void load   ();
		void unload ();

	private:
		GameStateManager* manager;
		Content* content;
		GameWindow* window;

		//TESTING OBJECTS
		TTF_Font* font;
		ui::Label lb;
		ui::Button bt;
		graphics::Sprite sheep;

		map::Map map;
};

#endif /* MENUSTATE_H_ */
