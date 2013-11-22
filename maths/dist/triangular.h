/*
 * triangular.h
 *
 *  Created on: 18/10/2013
 *      Author: drb
 */

#ifndef DISTTRI_H_
#define DISTTRI_H_

// Triangular Distribution

//TODO : Calculate the x value of a given a, b, c points and probability
//TODO : Calculate the probability of a point at x given a, b, c points
//TODO : give better names to this file
namespace maths
{
namespace dist
{
  double tri_rnd ( double min, double mode, double max );

} /* namespace dist */
} /* namespace math */

#endif /* DISTTRI_H_ */
