/*
 * rect.h
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#ifndef RECT_H_
#define RECT_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace maths
{

  bool isRectTouching (SDL_Rect* rect1, SDL_Rect* rect2);
  bool isRectTouching (const SDL_Rect &rect1, const SDL_Rect &rect2);


  bool isWholeRectInside (SDL_Rect* small, SDL_Rect* big );
  bool isWholeRectInside (const SDL_Rect &small, const SDL_Rect &big );

  void rectSubtract (SDL_Rect* rect, SDL_Point pt );
  void rectSubtract (SDL_Rect* rect, SDL_Rect pt );

} /* namespace math */

#endif /* RECT_H_ */
