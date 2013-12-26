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

#include "../etc/define.h"
#include "../etc/Camera.h"

class GameState
{
public:
    GameState();
    virtual ~GameState();

    //Each frame
    virtual void render (const Ldouble& delta, SDL_Renderer* renderer , const etc::Camera& camera );
    virtual void update (const Ldouble& delta);
    virtual void event (SDL_Event e , const Ldouble& delta);

    //Inital un/Load Assests
    virtual void load   ();
    virtual void unload ();

    bool is_loaded = false;

};

#endif /* GAMESTATE_H_ */
