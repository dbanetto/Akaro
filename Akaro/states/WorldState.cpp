#include "WorldState.h"

WorldState::WorldState( GameStateManager* Manager, GameWindow* Window, Content* Content )
{
	//ctor
	this->manager = Manager;
	this->content = Content;
	this->window = Window;
}

WorldState::~WorldState()
{
	//dtor
}

void WorldState::render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera )
{

}

void WorldState::update ( const Ldouble& delta )
{

}

void WorldState::event ( SDL_Event e , const Ldouble& delta )
{

}

//Inital un/Load Assests
void WorldState::load   ()
{

}
void WorldState::unload ()
{

}
