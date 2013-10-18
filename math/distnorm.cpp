/*
 * distnorm.cpp
 *
 *  Created on: 18/10/2013
 *      Author: drb
 */

#include "distnorm.h"

namespace math
{
  double dist_norm_zscore (double x , double mean, double sd )
  {
    // (X - x) / s.d
    // Z Score equation
    return (x - mean) / sd;
  }

} /* namespace math */
