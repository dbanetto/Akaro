/*
 * Point.cpp
 *
 *  Created on: 8/10/2013
 *      Author: drb
 */

#include "Point.h"
#include "../etc/string.h"

namespace maths {

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


/**
 * @param Value to added
 * @return sum of two points
 */
Point Point::operator+(const Point& in) const
{
    Point result;
    result.x = this->x + in.x;
    result.y = this->y + in.y;
    return result;

}

/**
 * @param Value to minus
 * @return subtraction of two Points
 */
Point Point::operator-(const Point& in) const
{
    Point result;
    result.x = this->x -in.x;
    result.y = this->y - in.y;
    return result;
}

/**
 * \Brief Converts Point to a String in (x,y) format
 *
 * @return String of Point (x,y) format
 */
std::string Point::str()
{
    //Default string setting
    return str('(',',',')');
}

/**
 * @param prefix - character before the first value
 * @param mid - mid char between the point values
 * @param postfix - the character at the end of teh string
 * @return
 */
std::string Point::str(char prefix, char mid , char postfix)
{
    return prefix + etc::convInt( this->x ) + mid + etc::convInt( this->y ) + postfix;
}

Point::~Point() { }

} /* namespace etc */
