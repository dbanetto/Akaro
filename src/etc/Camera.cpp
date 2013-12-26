/*
 * Camera.cpp
 *
 *  Created on: 26/12/2013
 *      Author: drb
 */

#include "Camera.h"

namespace etc
{

    Camera::Camera ()
    {
        // TODO Auto-generated constructor stub

    }

    Camera::~Camera ()
    {
        // TODO Auto-generated destructor stub
    }

    const SDL_Rect& Camera::getViewport()
    {
        return this->view;
    }

    void Camera::setBounds (int w, int h)
    {
        this->view.w = w;
        this->view.h = h;
    }

    void Camera::setPosition (int x, int y)
    {
        this->view.x = x;
        this->view.y = y;

    }

    SDL_Rect Camera::subCamPos( SDL_Rect pt )
    {
        pt.x -= this->view.x;
        pt.y -= this->view.y;
        return pt;
    }

} /* namespace etc */
