/*
 * colour.h
 *
 *  Created on: 9/10/2013
 *      Author: drb
 */

#ifndef COLOUR_H_
#define COLOUR_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace etc {

// TODO : Add more colours
enum Colour {
  COLOUR_BLACK,
  COLOUR_WHITE,
  COLOUR_GREEN,
  COLOUR_RED,
  COLOUR_BLUE
};

SDL_Color toColour (Colour colour);
SDL_Color toColour (Colour colour, Uint8 a);
SDL_Color toColour (Uint8 r , Uint8 g , Uint8 b , Uint8 a );
SDL_Color toColour (int r , int g , int b , int a );

} /* namespace etc */

#endif /* COLOUR_H_ */
