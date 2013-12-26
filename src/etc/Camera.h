/*
 * Camera.h
 *
 *  Created on: 26/12/2013
 *      Author: drb
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <SDL2/SDL.h>
#include "define.h"

namespace etc
{

    class Camera
    {
        public:
            Camera ();
            virtual ~Camera ();

            void render (const Ldouble& delta);
            void update (const Ldouble& delta);

            void setBounds (int w, int h);
            void setPosition (int x, int y);

            SDL_Rect subCamPos( SDL_Rect rect );

            const SDL_Rect& getViewport();

        private:
            SDL_Rect view;
    };

} /* namespace etc */

#endif /* CAMERA_H_ */
