/*
 * GameStateManager.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
    // TODO Auto-generated constructor stub
    current = nullptr;


}

GameStateManager::~GameStateManager()
{
    // TODO Auto-generated destructor stub
}

void GameStateManager::set_state (int state)
{
    if (this->current != nullptr) {
        this->current->unload();
    }
    this->current = this->states[state];
    this->current->load();
}

int GameStateManager::add_state (GameState* state)
{
    this->states.push_back( state );
    return this->states.size() - 1;
}
