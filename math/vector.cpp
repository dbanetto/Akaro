/*
 * vector.cpp
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#include "vector.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

namespace math
{
  /*
   * Rotation using point rotation around the origin ( more here http://en.wikipedia.org/wiki/Rotation_%28mathematics%29 )
   * Angle in degrees
  */
  std::vector<SDL_Point> translate (std::vector<SDL_Point> points, SDL_Point center , double angle, SDL_Point offset)
  {
      //Create output vector
      std::vector<SDL_Point> n_points;
      //Reserve the same amount of points
      n_points.reserve(points.size());
      //Pre-calculate sin and cos as they will not change
      double a_sin = 0;
      double a_cos = 1;
      if (angle == 180)
      {
          a_cos = -1;
      }
      else if (angle != 0)
      {
          a_sin = sin( (angle / 180.0) * M_PI );
          a_cos = cos( (angle / 180.0) * M_PI );
      }
      for (unsigned int i = 0; i < points.size(); i++)
      {
          SDL_Point pt;
          //Offset so the center is the origin of the points
          pt.x = (points[i].x - center.x);
          pt.y = (points[i].y - center.y);
          //No rotational translation needed if angle = 0
          double py = pt.y;
          double px = pt.x;
          if (angle == 180)
          {
              //Rotate the point around the origin by angle degrees
              pt.x = round(-px - py*a_sin);
              pt.y = round(px*a_sin - py);
          }
          else if (angle != 0)
          {
              //Rotate the point around the origin by angle degrees

              pt.x = round(px*a_cos - py*a_sin);
              pt.y = round(px*a_sin + py*a_cos);
          }
          //Returning the points back to before the origin change
          pt.x += center.x + offset.x;
          pt.y += center.y + offset.y;

          //Add them to the output list
          n_points.push_back(pt);
      }
      return n_points;
  }

  void translatept (std::vector<SDL_Point>* points, SDL_Point center , double angle, SDL_Point offset)
  {
      //Pre-calculate sin and cos as they will not change
      double a_sin = 0;
      double a_cos = 1;
      if (angle == 180)
      {
          a_cos = -1;
      }
      else if (angle != 0)
      {
          a_sin = sin( (angle / 180.0) * M_PI );
          a_cos = cos( (angle / 180.0) * M_PI );
      }
      for (unsigned int i = 0; i < (*points).size(); i++)
      {
          SDL_Point pt;
          //Offset so the center is the origin of the points
          pt.x = ((*points)[i].x - center.x);
          pt.y = ((*points)[i].y - center.y);
          //No rotational translation needed if angle = 0
          double py = pt.y;
          double px = pt.x;
          if (angle == 180)
          {
              //Rotate the point around the origin by angle degrees
              pt.x = round(-px - py*a_sin);
              pt.y = round(px*a_sin - py);
          }
          else if (angle != 0)
          {
              //Rotate the point around the origin by angle degrees

              pt.x = round(px*a_cos - py*a_sin);
              pt.y = round(px*a_sin + py*a_cos);
          }
          //Returning the points back to before the origin change
          pt.x += center.x + offset.x;
          pt.y += center.y + offset.y;

          //Add them to the output list
          (*points)[i] = pt;
      }
  }

  double distance (SDL_Point p1 , SDL_Point p2)
  {
      return SDL_sqrt ( SDL_pow(p2.x - p1.x, 2) + SDL_pow(p2.y - p1.y, 2) );
  }

  /*
   * Tests if a given point is within a polygon
   * Using ray casting algorithm http://en.wikipedia.org/wiki/Point_in_polygon
  */
  bool isPointInsidePolygon (SDL_Point point , std::vector<SDL_Point>* points)
  {
      //Code converted from pseudo code from http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
      //Credit for this snippet goes to http://stackoverflow.com/users/1830407/josh
      int i, j, nvert = points->size();
      bool c = false;

      for(i = 0, j = nvert - 1; i < nvert; j = i++)
      {
          if(  ( ( (*points)[i].y ) >= point.y) != ( ((*points)[j].y >= point.y) ) &&
                  (point.x <= ((*points)[j].x - (*points)[i].x) * (point.y - (*points)[i].y) / ((*points)[j].y - (*points)[i].y) + (*points)[i].x))

              c = !c;
      }

      return c;

  }

  bool isPolygonInsidePolygon(std::vector<SDL_Point>* pt , std::vector<SDL_Point>* polygon)
  {
      //Cycle through all the points of one polygon
      for (unsigned int i = 0; i < (*pt).size(); i++)
      {
          if ( isPointInsidePolygon( (*pt)[i] , polygon) )
          {
              return true;
          }
      }
      return false;
  }

} /* namespace math */
