/*
 * Texture.h
 *
 *  Created on: 14/11/2013
 *      Author: drb
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <string>
#include <vector>


namespace graphics
{

    class Texture
    {
        public:
            Texture ();
            Texture (SDL_Renderer* renderer,std::string file);
            Texture (const Texture& tex);

            virtual ~Texture ();

            bool load (SDL_Renderer* renderer,std::string file);
            bool load (SDL_Renderer* renderer,  std::string file, int columns, int rows);
            bool load (SDL_Renderer* renderer, std::string file, std::vector<SDL_Rect> sprite_map);

            SDL_Texture* getTexture();
            SDL_Rect* getSprite(int column, int row);
            SDL_Rect* getSprite(int index);

        private:
            SDL_Texture* texture;
            std::vector<SDL_Rect> sprite_map;
            bool is_loaded;
            int columns;
            int rows;
    };

} /* namespace graphics */

#endif /* TEXTURE_H_ */
