/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

//Cross platform
//SDL_timer.h is used instead of SDL.h due to build times


#include "Timer.h"

Timer::Timer()
{
    //Initialize the variables
    this->startTicks = 0;
    this->pausedTicks = 0;
    this->paused = false;
    this->started = false;
}

void Timer::start()
{
    //Start the timer
    this->started = true;

    //Unpause the timer
    this->paused = false;

    //Get the current clock time
    this->startTicks = SDL_GetPerformanceCounter();
}

void Timer::stop()
{
    //Stop the timer
    this->started = false;

    //Unpause the timer
    this->paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( this->started == true ) && ( this->paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        this->pausedTicks = SDL_GetPerformanceCounter() - this->startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( this->paused == true )
    {
        //Unpause the timer
        this->paused = false;

        //Reset the starting ticks
        this->startTicks = SDL_GetPerformanceCounter() - this->pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

double long Timer::get_ticks()
{
    //If the timer is running
    if( this->started == true )
    {
        //If the timer is paused
        if( this->paused == true )
        {
            //Return the number of ticks when the timer was paused
            return this->pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return (double long)(SDL_GetPerformanceCounter() - this->startTicks) / (double long)(SDL_GetPerformanceFrequency());
        }
    }

    //If the timer isn't running
    return 0;
}

Uint64 Timer::get_ticks_raw()
{
    //If the timer is running
    if( this->started == true )
    {
        //If the timer is paused
        if( this->paused == true )
        {
            //Return the number of ticks when the timer was paused
            return this->pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetPerformanceCounter() - this->startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return this->started;
}

bool Timer::is_paused()
{
    return this->paused;
}
