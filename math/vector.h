/*
 * vector.h
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <vector>

namespace math
{
  std::vector<SDL_Point> translate (std::vector<SDL_Point> points, SDL_Point center , double angleDeg , SDL_Point Offset);
  void translatept (std::vector<SDL_Point>* points, SDL_Point center , double angleDeg , SDL_Point OffSet);

  double distance (SDL_Point p1 , SDL_Point p2);
} /* namespace math */

#endif /* VECTOR_H_ */
