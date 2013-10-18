/*
 * distnorm.h
 *
 *  Created on: 18/10/2013
 *      Author: drb
 */

#ifndef DISTNORM_H_
#define DISTNORM_H_

//Normal Distribution

namespace math
{
  //TODO : Add probability (double between 0 and 1) to Z Score function
  //TODO : Add a Z score to value (with given s.d. and mean)

  double dist_norm_zscore ( double x,  double mean, double sd );

} /* namespace math */

#endif /* NORMDIST_H_ */
