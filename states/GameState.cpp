/*
 * GameState.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#include "GameState.h"
#include <iostream>

GameState::GameState()
{
    // TODO Auto-generated constructor stub
}


GameState::~GameState()
{
    // TODO Auto-generated destructor stub
}



//Each frame
void GameState::render (const double& delta, SDL_Renderer* renderer)
{
    std::cout << "WARNING : Base render function for GameState is called" << std::endl;
}

void GameState::update (const double& delta)
{
    std::cout << "WARNING : Base update function for GameState is called" << std::endl;
}

void GameState::event (SDL_Event e , const double& delta)
{
    std::cout << "WARNING : Base event function for GameState is called" << std::endl;
}

//Inital un/Load Assests
void GameState::load   ()
{
    std::cout << "WARNING : Base load function for GameState is called" << std::endl;
}

void GameState::unload ()
{
    std::cout << "WARNING : Base unload function for GameState is called" << std::endl;
}
