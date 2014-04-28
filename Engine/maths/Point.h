/*
 * Point.h
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#ifndef POINT_H_
#define POINT_H_

// TODO : Add operators ( += , -= , == )
#include <string>
#include "../etc/define.h"

namespace maths
{

	class Point
	{
		public:
			Point();
			Point( const Point& p );
			Point( double xy );
			Point( double x, double y );

			virtual ~Point();

			//Operators

			Point operator+( const Point& ) const;
			Point operator-( const Point& ) const;


			//To String Function
			std::string str();
			std::string str( char prefix, char mid , char postfix );

			Ldouble x , y;
	};

} /* namespace etc */

#endif /* POINT_H_ */
