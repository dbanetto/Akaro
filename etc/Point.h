/*
 * Point.h
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#ifndef POINT_H_
#define POINT_H_

// TODO : Add operators ( += , -= , - , + , == )

namespace etc {

class Point {
public:
    Point();
    Point(const Point& p);
    Point(double xy);
    Point(double x, double y);

    virtual ~Point();

    double x , y;
};

} /* namespace etc */

#endif /* POINT_H_ */
