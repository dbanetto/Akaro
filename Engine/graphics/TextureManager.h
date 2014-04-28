/*
 * TextureManager.h
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <map>
#include <string>
#include "Texture.h"

namespace graphics
{

	class TextureManager
	{
		public:
			TextureManager ();
			TextureManager ( SDL_Renderer* renderer );
			virtual ~TextureManager ();
			bool load ( std::string file , std::string name );
			bool load ( std::string file , std::string name , int columns , int rows );

			bool exists ( std::string name );

			Texture* getTexture ( std::string name );

			void unload ();

		private:
			std::map<std::string, Texture> textures;
			SDL_Renderer* renderer;
	};

} /* namespace graphics */

#endif /* TEXTUREMANAGER_H_ */
