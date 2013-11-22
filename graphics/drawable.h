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

#include "../maths/Point.h"

namespace graphics
{
/**
 * @brief Base class of all object to be rendered on-screen
 */
  class drawable
  {
  public:
    drawable();
    virtual ~drawable() = 0;

    virtual void render (const double& delta, SDL_Renderer* renderer) = 0;
    virtual void update (const double& delta) = 0;


    void setPosition (maths::Point pos);
    void setPosition (SDL_Point pos);
    void setPosition (double x , double y);

    SDL_Rect getRect ();
    maths::Point getPosition ();

  protected:
    //Position and rectangular area
    SDL_Rect area;
    maths::Point pos;

  };

} /* namespace graphics */

#endif /* DRAWABLE_H_ */
