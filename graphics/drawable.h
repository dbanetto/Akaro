/*
 * drawable.h
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace graphics
{

  class drawable
  {
  public:
    drawable();
    virtual ~drawable() = 0;

    virtual void render (const double& delta, SDL_Renderer* renderer) = 0;
    virtual void update (const double& delta) = 0;


    void setPosition (SDL_Point pos);
    void setPosition (int x , int y);

    SDL_Rect getRect ();
    SDL_Point getPosition ();

  protected:
    //Position and rectangular area
    SDL_Rect pos;

  };

} /* namespace graphics */

#endif /* DRAWABLE_H_ */
