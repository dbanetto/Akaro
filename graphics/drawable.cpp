/*
 * drawable.cpp
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#include "drawable.h"

namespace graphics
{

  drawable::drawable()
  {
    //Set the rectangle to be (0,0,0,0)
    this->pos.x = 0;
    this->pos.y = 0;
    this->pos.w = 0;
    this->pos.h = 0;

  }

  void drawable::setPosition (SDL_Point pos)
  {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
  }

  void drawable::setPosition (int x , int y)
  {
    this->pos.x = x;
    this->pos.y = y;
  }

  SDL_Rect drawable::getRect ()
  {
    return this->pos;
  }

  SDL_Point drawable::getPosition ()
  {
    SDL_Point pt;
    pt.x = this->pos.x;
    pt.y = this->pos.y;
    return pt;
  }

  drawable::~drawable()
  {
  }

} /* namespace graphics */
