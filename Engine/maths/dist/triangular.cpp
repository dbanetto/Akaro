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
	namespace dist
	{
		//Reverse triangular distribution, from probability to x value
		double tri_rnd ( double a, double b, double c )
		{
			//Get Random number between 0 and 1
			double prob = ( double )rand() / RAND_MAX;
			//Calculate the height of the distribution triangle
			double h = 2 / ( b - a );

			//Calculate the position of the probability in the triangle
			double D =  b * c - a * c - a * b + a * a;
			double E =  a * a - D * prob;

			//Find the position of x when the area under is equal to prob
			double x = ( 2 * a + sqrt( 4 * a * a - 4 * E ) ) / 2;

			//Height of point at point x
			double l = ( 2 * ( x - a ) ) / ( ( b - a ) * ( c - a ) );

			//Is it higher than the tallest point of the distribution?
			if ( l > h )
			{
				//Yes
				//x = (c-a)/(b-a);
				double P = prob - ( c - a ) / ( b - a );
				double g = ( b * b - a * b - b * c + a * c ) * ( P - ( b - c ) / ( b - a ) );
				E = ( b * b ) + g;

				x = ( 2 * b - sqrt( 4 * ( b * b ) - 4 * E ) ) / 2;
			}
			else
			{
				//No
				//All done
			}

			//Return the x coordinate as the given value
			return x;
		}
	} /* namespace dist */
} /* namespace math */
