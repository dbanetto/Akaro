/*
 * normal.cpp
 *
 *  Created on: 18/10/2013
 *      Author: drb
 */

#include "normal.h"

namespace maths
{
	namespace dist
	{
		double norm_zscore (double x , double mean, double sd )
		{
			// (X - x) / s.d = Z
			// Z Score equation
			return (x - mean) / sd;
		}

		double norm_inverse_zscore ( double z,  double mean, double sd )
		{
			//  Z * s.d. + x = X
			return (sd * z) + mean;
		}

	} /* namespace dist */
} /* namespace math */
