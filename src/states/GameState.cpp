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
}


GameState::~GameState()
{
}



//Each frame
void GameState::render (const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera)
{
    std::cout << "WARNING : Base render function for GameState is called" << std::endl;
}

void GameState::update (const Ldouble& delta)
{
    std::cout << "WARNING : Base update function for GameState is called" << std::endl;
}

void GameState::event (SDL_Event e , const Ldouble& delta)
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
