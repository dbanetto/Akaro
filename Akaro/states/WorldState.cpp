#include "WorldState.h"

#include <iostream>

WorldState::WorldState( GameStateManager* Manager, GameWindow* Window, Content* Content )
{
	//ctor
	this->manager = Manager;
	this->content = Content;
	this->window = Window;

	this->is_loaded = false;
	this->cur_map = nullptr;
}

WorldState::~WorldState()
{
	//dtor
}

void WorldState::render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera )
{
	if (!this->is_loaded || cur_map == nullptr)
		return;

	if (cur_map != nullptr){

		cur_map->render( delta , this->window->getTextures() , camera);
	}
}

void WorldState::update ( const Ldouble& delta )
{
	if (!this->is_loaded)
		return;
}

void WorldState::event ( SDL_Event e , const Ldouble& delta )
{

}

//Inital un/Load Assests
void WorldState::load   ()
{
	cur_map = this->content->Maps()->get(this->content->Maps()->getCurrentMapName() );

	std::cout << "World State Loaded " << this->content->Maps()->getCurrentMapName() << std::endl;
	this->is_loaded = true;
}
void WorldState::unload ()
{
	this->is_loaded = false;
}
