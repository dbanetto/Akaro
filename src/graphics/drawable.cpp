/*
 * drawable.cpp
 *
 *  Created on: 15/10/2013
 *      Author: drb
 */

#include "drawable.h"

namespace graphics
{

	drawable::drawable()
	{
		//Set the rectangle to be (0,0,0,0)
		this->pos.x = 0;
		this->pos.y = 0;

		this->area.x = 0;
		this->area.y = 0;
		this->area.w = 0;
		this->area.h = 0;

		this->adjust_camera = false;
	}

	void drawable::setPosition (SDL_Point pos)
	{
		this->pos.x = pos.x;
		this->pos.y = pos.y;

		this->area.x = pos.x;
		this->area.y = pos.y;
	}

	void drawable::setPosition (maths::Point pos)
	{
		this->pos.x = pos.x;
		this->pos.y = pos.y;

		this->area.x = (int)pos.x;
		this->area.y = (int)pos.y;
	}
	void drawable::changePosition (Ldouble x , Ldouble y)
	{
		this->pos.x += x;
		this->pos.y += y;

		this->area.x = (int)pos.x;
		this->area.y = (int)pos.y;
	}
	void drawable::setPosition (Ldouble x , Ldouble y)
	{
		this->pos.x = x;
		this->pos.y = y;

		this->area.x = (int)pos.x;
		this->area.y = (int)pos.y;
	}

	SDL_Rect drawable::getRect ()
	{
		return this->area;
	}

	maths::Point drawable::getPosition ()
	{
		return this->pos;
	}

	void drawable::setAdjustCamera(bool var)
	{
		this->adjust_camera = var;
	}

	drawable::~drawable()
	{
	}

} /* namespace graphics */
