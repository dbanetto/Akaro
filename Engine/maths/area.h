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
#include "Point.h"

namespace maths
{

	double area_triangle ( const double& base , const double& height );
	double area_triangle ( const SDL_Point& a , const SDL_Point& b,  const SDL_Point& c );
	double area_triangle ( const Point& a , const Point& b,  const Point& c );

	double area_points ( std::vector<SDL_Point> points , SDL_Point center );
	double area_rect   ( SDL_Rect rect );

} /* namespace math */

#endif /* AREA_H_ */
