/*
 * rect.cpp
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#include "rect.h"

namespace maths
{

  bool isRectTouching (SDL_Rect* aRect, SDL_Rect* bRect)
  {
      /*
      * Point's for rectangle (x,y) , (x+w,y) , (x+w,y+h) , (x,y+h)
      * Checks if the points are in the bounds of each other
      * Pointers to SDL_rect's are used for faster(?) usage of properties
      */
      if (aRect->x < (bRect->x + bRect->w) && (aRect->x + aRect->w) > bRect->x &&
              aRect->y < (bRect->y + bRect->h) && (aRect->y + aRect->h) > bRect->y)
      {
          return true;
      }
      else
      {
          return false;
      }
  }

  bool isRectTouching (const SDL_Rect &aRect, const SDL_Rect &bRect )
  {
      /*
        * Point's for rectangle (x,y) , (x+w,y) , (x+w,y+h) , (x,y+h)
        * Checks if the points are in the bounds of each other
        * Pointers to SDL_rect's are used for faster(?) usage of properties
        */
        if (aRect.x < (bRect.x + bRect.w) && (aRect.x + aRect.w) > bRect.x &&
                aRect.y < (bRect.y + bRect.h) && (aRect.y + aRect.h) > bRect.y)
        {
            return true;
        }
        else
        {
            return false;
        }
  }

  void rectSubtract (SDL_Rect* rect, SDL_Point pt )
  {
      rect->x -= pt.x;
      rect->y -= pt.y;
  }

  void rectSubtract (SDL_Rect* rect, SDL_Rect pt )
  {
      rect->x -= pt.x;
      rect->y -= pt.y;
  }

  bool isWholeRectInside (SDL_Rect* small, SDL_Rect* big )
  {
      if ( small->x > big->x && small->y > big->y
              && (small->x + small->w) < (big->x + big->w) && (small->y + small->h) < (big->y + big->h) )
      {
          return true;
      }
      else
      {
          return false;
      }
  }

  bool isWholeRectInside (const SDL_Rect &small, const SDL_Rect &big )
  {
      if ((small.x > big.x) == false)
    	  return false;
      if ((small.y > big.y) == false)
          	  return false;
      if (((small.x + small.w) < (big.x + big.w)) == false)
          	  return false;
      if (((small.y + small.h) < (big.y + big.h)) == false)
          	  return false;

      return true;
  }
} /* namespace math */
