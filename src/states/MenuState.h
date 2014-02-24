/*
 * MenuState.h
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "GameState.h"
#include "GameStateManager.h"
#include "../GameWindow.h"
#include "../graphics/Sprite.h"
#include "../map/Map.h"

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
