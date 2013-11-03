/*
 * triangular.cpp
 *
 *  Created on: 18/10/2013
 *      Author: drb
 */

#include "triangular.h"
#include <random>
#include "../area.h"
#include "../Point.h"
#include <iostream>

namespace maths
{
  //Reverse triangular distribution, from probability to x value
  double dist_tri_rnd ( double a, double b, double c )
  {
    //Get Random number between 0 and 1
    double prob = (double)rand()/RAND_MAX;
    //Calculate the height of the distribution triangle
    double h = 1 / (b - a);

    //Calculate the position of the probability in the triangle
    double D =  b*c - a*c - a*b + a*a;
    double E =  a*a - D * prob;

    //Find the position of x when the area under is equal to prob
    double x = (2*a + sqrt(4*a*a - 4*E ) ) / 2;

    //Height of point at point x
    double l = (2 * ( x - a )) / ((b-a)*(c-a));

    //Is it higher than the tallest point of the distribution?
    if (l > h) {
        //Yes
        //Then it is apart of the second equation
        //Find the point
        D =  b*b - b*c - a*b + a*c;
        E =  b*b - D * prob;

        x = (2*b + sqrt(4*b*b - 4*E ) ) / 2;
        std::cout << x << std::endl;
    } else {
        //No
        //All done
        std::cout << x << std::endl;
    }

    //Return the x coordinate as the given value
    return x;
  }

} /* namespace math */
