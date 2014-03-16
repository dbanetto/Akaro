/*
 * GameStateManager.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
	current = nullptr;
}

GameStateManager::~GameStateManager()
{
	this->unload();
}

void GameStateManager::unload()
{
    // Delete all the GameStates as they were made with new statements
    for (auto& obj : this->states)
    {
        if (obj.second->is_loaded)
        {
            obj.second->unload();
        }
        delete obj.second;
    }
    this->states.clear();
}

void GameStateManager::set_state (std::string state_name)
{
	if (this->exists( state_name) == false)
	{
		return;
	}

	if (this->current != nullptr)
	{
		this->current->unload();
	}
	this->current = this->states[state_name];
	this->current_name = state_name;
	this->current->load();
}

bool GameStateManager::add_state (std::string state_name , GameState* state)
{
	if (this->exists(state_name) == false)
	{
		this->states[state_name] = state;
		return true;
	}
	else
	{
		return false;
	}
}

bool GameStateManager::exists (std::string state_name)
{
	if (this->states.find(state_name) == this->states.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}
