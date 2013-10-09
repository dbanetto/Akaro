/*
 * Point.cpp
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#include "Point.h"

namespace etc {

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(const Point& p) {
    this->x = p.x;
    this->y = p.y;
}

Point::Point(double xy) {
    this->x = xy;
    this->y = xy;
}

Point::Point(double x , double y) {
    this->x = x;
    this->y = y;
}

Point::~Point() { }



} /* namespace etc */
