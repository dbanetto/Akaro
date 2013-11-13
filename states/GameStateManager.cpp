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
    // Delete all the GameStates as they were made with new statements
    for (auto& obj : this->states) {
        if (obj.second->is_loaded) {
            obj.second->unload();
        }
        delete obj.second;
    }
}

void GameStateManager::set_state (std::string state_name)
{
    if (this->exists( state_name) == false) {
        return;
    }

    if (this->current != nullptr) {
        this->current->unload();
    }
    this->current = this->states[state_name];
    this->current_name = state_name;
    this->current->load();
}

int GameStateManager::add_state (std::string state_name , GameState* state)
{
    this->states[state_name] = state;
    return this->states.size() - 1;
}

bool GameStateManager::exists (std::string state_name)
{
    if (this->states.find(state_name) == this->states.end()) {
        return false;
    } else {
        return true;
    }
}
