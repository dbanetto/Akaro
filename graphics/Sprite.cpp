/*
 * Sprite.cpp
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#include "Sprite.h"

namespace graphics
{

    Sprite::Sprite ()
    {
        // TODO Auto-generated constructor stub
        this->tex = nullptr;
        this->sprite_map_index = 0;
        this->rot = 0;
        this->flip = SDL_FLIP_NONE;
    }

    Sprite::Sprite (Texture* texture ,SDL_Rect Position, int SpriteMapIndex , double Rotation , SDL_Point CenterofRotation, SDL_RendererFlip flip)
    {
        this->pos = Position;
        this->tex = texture;
        this->sprite_map_index = SpriteMapIndex;
        this->rot = Rotation;
        this->cor = CenterofRotation;
        this->flip = flip;
    }

    Sprite::~Sprite ()
    {
        // TODO Auto-generated destructor stub
    }

    void Sprite::render (const double& delta, SDL_Renderer* renderer)
    {
        SDL_Texture* texture = this->tex->getTexture();
        SDL_RenderCopyEx(renderer , texture , this->tex->getSprite(this->sprite_map_index) ,  &(this->pos) , this->rot , &(this->cor) , this->flip );
    }

    void Sprite::update (const double& delta)
    {

    }

    //Getters and Setters
    void Sprite::setTexture (Texture* texture)
    {
        this->tex = texture;
    }
    void Sprite::setFlip (SDL_RendererFlip flip)
    {
        this->flip = flip;
    }
    void Sprite::setCenterOfRotation (SDL_Point pt)
    {
        this->cor = pt;
    }
    void Sprite::setRotation (double rot)
    {
        this->rot = rot;
    }
    void Sprite::setSpriteMapIndex (int sprite_map_index)
    {
        this->sprite_map_index = sprite_map_index;
    }

    Texture* Sprite::getTexture()
    {
        return this->tex;
    }
    SDL_RendererFlip Sprite::getFlip()
    {
        return this->flip;
    }
    SDL_Point Sprite::getCenterOfRotation()
    {
        return this->cor;
    }
    double Sprite::getRotation()
    {
        return this->rot;
    }
    int Sprite::getSpriteMapIndex ()
    {
        return this->sprite_map_index;
    }

} /* namespace graphics */
