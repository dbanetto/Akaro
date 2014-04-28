/*
 * GameStateManager.h
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <map>
#include "GameState.h"

class GameStateManager
{
	public:
		GameStateManager();
		virtual ~GameStateManager();
		void set_state ( std::string state_name );

		bool add_state ( std::string state_name , GameState* state );

		bool exists ( std::string state_name );

		void unload();

		GameState* current;
		std::string current_name;
	private:
		std::map<std::string , GameState*> states;
};

#endif /* GAMESTATEMANAGER_H_ */
