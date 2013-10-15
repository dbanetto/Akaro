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

  double areaOfPoints ( std::vector<SDL_Point> points , SDL_Point center );
  double areaOfRect   (SDL_Rect rect);

} /* namespace math */

#endif /* AREA_H_ */
