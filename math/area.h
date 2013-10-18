/*
 * area.h
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#ifndef AREA_H_
#define AREA_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <vector>

namespace math
{

  double area_triangle (double base , double height);
  double area_triangle ( SDL_Point a , SDL_Point b,  SDL_Point c);

  double area_points ( std::vector<SDL_Point> points , SDL_Point center );
  double area_rect   (SDL_Rect rect);

} /* namespace math */

#endif /* AREA_H_ */
