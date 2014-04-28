/*
 * drawable.h
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include "../etc/Camera.h"
#include "../maths/Point.h"

namespace graphics
{
	/**
	 * @brief Base class of all object to be rendered on-screen
	 */
	class drawable
	{
		public:
			drawable();
			virtual ~drawable() = 0;

			virtual void render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera ) = 0;
			virtual void update ( const Ldouble& delta ) = 0;


			void setPosition ( maths::Point pos );
			void setPosition ( SDL_Point pos );
			void setPosition ( Ldouble x , Ldouble y );

			void changePosition ( Ldouble x , Ldouble y );

			SDL_Rect getRect ();
			maths::Point getPosition ();

			void setAdjustCamera( bool var );

		protected:
			//Position and rectangular area
			SDL_Rect area;
			maths::Point pos;
			/**
			 * @note Sets if a object is effected by camera
			 */
			bool adjust_camera;

	};

} /* namespace graphics */

#endif /* DRAWABLE_H_ */
