/*
 * Sprite.h
 *
 *  Created on: 13/11/2013
 *      Author: drb
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "drawable.h"
#include "Texture.h"


namespace graphics
{
	/**
	 * @brief Base Class for all on-screen entities with Game logic
	 */
	class Sprite : public graphics::drawable
	{
		public:
			Sprite ();
			Sprite (Texture* texture ,SDL_Rect Position, int SpriteMapIndex , double Rotation , SDL_Point CenterofRotation, SDL_RendererFlip flip);
			virtual ~Sprite ();

			virtual void render (const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera);
			virtual void update (const Ldouble& delta);

			void setTexture (Texture* texture);
			void setFlip (SDL_RendererFlip flip);
			void setCenterOfRotation (SDL_Point pt);
			void setRotation (double rot);
			void setSpriteMapIndex (int sprite_map_index);

			Texture* getTexture();
			SDL_RendererFlip getFlip();
			SDL_Point getCenterOfRotation();
			double getRotation();
			int getSpriteMapIndex ();
		private:
			Texture* tex;
			SDL_RendererFlip flip;
			SDL_Point cor; // Center of Rotation
			double rot; //rotation in rads
			int sprite_map_index;
	};

} /* namespace graphics */

#endif /* SPRITE_H_ */
