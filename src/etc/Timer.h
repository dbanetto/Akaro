/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#pragma once

#ifndef TIMER_H_
#define TIMER_H_

#if __GNUC__
#include <SDL2/SDL_timer.h>
#else
#include "SDL_timer.h"
#endif

#include "define.h"

class Timer
{
	public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint64 get_ticks_raw();
		Ldouble get_ticks();


		//Checks the status of the timer
		bool is_started();
		bool is_paused();

	private:
		//The clock time when the timer started
		Uint64 startTicks;

		//The ticks stored when the timer was paused
		Uint64 pausedTicks;

		//The timer status
		bool paused;
		bool started;
};

#endif
