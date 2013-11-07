/*
 * GameStateManager.h
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <vector>
#include "GameState.h"

class GameStateManager
{
public:
    GameStateManager();
    virtual ~GameStateManager();
    void set_state (int state);

    int add_state (GameState* state);

    GameState* current;
private:
    std::vector<GameState*> states;
};

#endif /* GAMESTATEMANAGER_H_ */
