/*
 * area.cpp
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#include "area.h"
#include <iostream>
#include <vector>
#include <limits>
#include "math.h"
#include <algorithm>
#include "vector.h"

namespace math
{

bool double_gtr_sort (double a, double b)
{
    return (a>b);
}

double areaOfPoints ( std::vector<SDL_Point> points , SDL_Point center )
{
    double area = 0;
    /*
     * For each two points in the polygon calculate a triangle
     * with the center point as a common point with all triangles
     * The area is calculated wit the Horen's Formula and summed
     */
    for (unsigned int i = 0; i < points.size(); i ++)
    {

        //Check if this is the first point and pair it with the last point
        unsigned in = (i == 0 ? points.size() -1 : i -1 );

        std::vector<double> lengths;
        lengths.reserve(3);
        lengths.resize(3);
        // http://en.wikipedia.org/wiki/Heron%27s_formula
        lengths[0] = ( distance(points[i] , points[in] ));
        lengths[1] = ( distance(center , points[i] ) );
        lengths[2] = ( distance(center , points[in] ) );

        //Sort list to gain Numerical stability so it can be generally used
        std::sort (lengths.begin() , lengths.end() , double_gtr_sort );

        // Written version of equation
        // http://upload.wikimedia.org/math/1/7/c/17c41c9c2a57227d91fb7921c6ef78f4.png
        area += 0.25 * SDL_sqrt(
                    (lengths[0] + (lengths[1] + lengths[2])) *
                    (lengths[2] - (lengths[0] - lengths[1])) *
                    (lengths[2] + (lengths[0] - lengths[1])) *
                    (lengths[0] + (lengths[1] - lengths[2]))
                );
    }
    return area;
}

double areaOfRect (SDL_Rect rect)
{
  //Simple area of a rectangle
  return rect.w * rect.h;
}


} /* namespace math */
