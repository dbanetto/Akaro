/*
 * env.cpp
 *
 *  Created on: 7/10/2013
 *      Author: drb
 */


#include "env.h"

#include <iostream>
#include <iomanip>

#if __GNUC__
#include "SDL2\SDL.h"
#else
#include "SDL.h"
#endif

namespace etc {

void printSystemInfo()
{
	//Render Devices
	SDL_version ver;
	SDL_GetVersion( &ver );
	std::cout << "SDL Version:" << (int)(ver.major) << "." << (int)(ver.minor) << "." << (int)(ver.patch) << std::endl;

	std::cout << std::endl;

	//CPU
	std::cout << "CPU Cache Size:" << SDL_GetCPUCacheLineSize() << std::endl;
	std::cout << "CPU Cache Size :" << SDL_GetCPUCount() << std::endl;

	std::cout << std::endl;

	//Video Drivers
	std::cout << "Number of Displays:" << SDL_GetNumVideoDisplays() << std::endl;
	std::cout << "Current Video Driver:" << SDL_GetCurrentVideoDriver() << std::endl;
	int vid_drivers = SDL_GetNumVideoDrivers();
	for (int n =0; n < vid_drivers; n++) {
		std::cout << "Available Video Driver "  << n << ":" << SDL_GetVideoDriver(n) << std::endl;
	}

	std::cout << std::endl;

	//Joystick and Game Controller
	int num_joy, i;
	num_joy = SDL_NumJoysticks();
	std::cout << num_joy << " JoyStick(s) found" << std::endl;
	for(i = 0; i < num_joy; i++)
	{
	  SDL_Joystick *joystick = SDL_JoystickOpen(i);
	  std::cout << "Name:" << SDL_JoystickName(joystick) << std::endl;
	  std::cout << "JoyStick Name:" << SDL_JoystickNameForIndex(i) << std::endl;
	  std::cout << "Is Game Controller:" << SDL_IsGameController(i) << std::endl;
	  std::cout << "Number of Axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
	  std::cout << "Number of Buttons:" << SDL_JoystickNumButtons(joystick) << std::endl;
	  std::cout << "Number of Balls:" << SDL_JoystickNumBalls(joystick) << std::endl;
	  std::cout << "Number of Hats:" << SDL_JoystickNumHats(joystick) << std::endl;

	  SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(i);
	  std::cout << "GUID:";
	  for (int k =0; k < 16; k++) {
		  std::cout << std::hex << (guid.data[k] + 48);
		  if (k % 4 == 0 && k != 0) {
			  std::cout << "-";
		  }
	  }
	  std::cout << std::endl;

	  SDL_JoystickClose(joystick);
	  if ( SDL_IsGameController(i) == SDL_TRUE ) {
		  std::cout << "Controller Type:" << SDL_GameControllerNameForIndex(i) << std::endl;
	  }

	}

	std::cout << std::endl;

	//Audio Drivers
	std::cout << "Audio Drivers" << std::endl;
	std::cout << "Current Audio Drivers:" << SDL_GetCurrentAudioDriver() << std::endl;
	int audio = SDL_GetNumAudioDrivers();
	for (int i = 0; i < audio; i++) {
		std::cout << "Audio Driver " <<  i << ":" << SDL_GetAudioDriver(i) << std::endl;
	}

	std::cout << std::endl;

	//Audio Devices
	std::cout << "Audio Devices" << std::endl;
	int count = SDL_GetNumAudioDevices(0);
	for (int i = 0; i < count; i++ ) {
		std::cout << "Audio device " <<  i << ":" << std::string(SDL_GetAudioDeviceName(i, 0)) << std::endl;
	}
}

} /* namespace etc */
