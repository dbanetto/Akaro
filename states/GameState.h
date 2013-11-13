/*
 * GameState.h
 *
 *  Created on: Nov 6, 2013
 *      Author: drb
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

class GameState
{
public:
    GameState();
    virtual ~GameState();

    //Each frame
    virtual void render (const double& delta, SDL_Renderer* renderer);
    virtual void update (const double& delta);
    virtual void event (SDL_Event e , const double& delta);

    //Inital un/Load Assests
    virtual void load   ();
    virtual void unload ();

    bool is_loaded = false;

};

#endif /* GAMESTATE_H_ */
