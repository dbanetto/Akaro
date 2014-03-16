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
#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#else
#include "SDL.h"
#endif

namespace etc
{

	void printSystemInfo()
	{
		//Render Devices
		SDL_version ver;
		SDL_GetVersion( &ver );
		std::cout << "SDL Version : " << (int)(ver.major) << "." << (int)(ver.minor) << "." << (int)(ver.patch) << std::endl;
		std::cout << "Platform : " << SDL_GetPlatform() << std::endl;

		char* base_path;
		base_path = SDL_GetBasePath ();
		std::cout << "Base Path : " << base_path << std::endl;
		delete base_path;

		char* pref_path;
		//ORG and APP names are subject to change
		pref_path = SDL_GetPrefPath( "blb" , "akaro" );
		std::cout << "Preferred Path : " << pref_path << std::endl;
		delete pref_path;

		std::cout << std::endl;

		//CPU and RAM
		std::cout << "CPU Cache Size : " << SDL_GetCPUCacheLineSize() << std::endl;
		std::cout << "CPU Count : " << SDL_GetCPUCount() << std::endl;
		std::cout << "RAM : " << SDL_GetSystemRAM() << "MiB" << std::endl;

		std::cout << std::endl;

		//Power
		int secs  = 0, pct = 0;
		SDL_PowerState state = SDL_GetPowerInfo(&secs , &pct);
		switch (state)
		{
			case (SDL_POWERSTATE_ON_BATTERY):
				std::cout << "Battery Status : Discharging " << pct << "% " << secs/60 << "mins" << std::endl;
				break;
			case (SDL_POWERSTATE_CHARGING):
				std::cout << "Battery Status : Charging " << pct << "% " << secs/60 << "mins" << std::endl;
				break;
			case (SDL_POWERSTATE_CHARGED):
				std::cout << "Battery Status : Charged " << pct << "% " << secs/60 << "mins" << std::endl;
				break;
			case (SDL_POWERSTATE_NO_BATTERY):
				std::cout << "Battery Status : No Battery " << std::endl;
				break;
			case (SDL_POWERSTATE_UNKNOWN):
				std::cout << "Battery Status : Unknown" << std::endl;
		}


		std::cout << std::endl;

		//Other has (CPU) checks
		std::cout << "Has 3DNow : " << ( SDL_Has3DNow() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has Alti Vec : " << ( SDL_HasAltiVec()  == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has MMX : " << ( SDL_HasMMX() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has RDTSC : " << ( SDL_HasRDTSC() == 1 ? "true" : "false" ) << std::endl;

		std::cout << std::endl;

		//SSE Check
		std::cout << "Has SSE : " << ( SDL_HasSSE() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has SSE 2 : " << ( SDL_HasSSE2() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has SSE 3 : " << ( SDL_HasSSE3() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has SSE 4.1 : " << ( SDL_HasSSE41() == 1 ? "true" : "false" ) << std::endl;
		std::cout << "Has SSE 4.2 : " << ( SDL_HasSSE42() == 1 ? "true" : "false" ) << std::endl;



		std::cout << std::endl;

		std::cout << "Number of Displays : " << SDL_GetNumVideoDisplays() << std::endl;

		std::cout << std::endl;

		for(int i = 0; i < SDL_GetNumVideoDisplays(); i++)
		{

			std::cout << "Display Name " << i << " : " << SDL_GetDisplayName(i) << std::endl;

			SDL_DisplayMode desk;
			SDL_GetDesktopDisplayMode( i , &desk );

			SDL_Rect rect;
			SDL_GetDisplayBounds(i , &rect);
			std::cout << "Desktop Display Position " << i << " : { " << rect.x << " , " << rect.y << " }" << std::endl;

			std::cout << "Desktop Display Resolution " << i << " : " << desk.w << 'x' << desk.h << std::endl;
			std::cout << "Desktop Display Refresh " << i << " : " << desk.refresh_rate << std::endl;
			switch (desk.format)
			{
				case (SDL_PIXELFORMAT_RGB888):
					std::cout << "Desktop Display Format : RGB-888" << std::endl;
					break;
				case (SDL_PIXELFORMAT_RGB565):
					std::cout << "Desktop Display Format : RGB-565" << std::endl;
					break;
				default:
					std::cout << "Desktop Display Format : " << desk.format << std::endl;
					break;
			}
			std::cout << std::endl;
#ifdef PRINT_ALL_DISPLAY_MODES
			for (int n =0; n < SDL_GetNumDisplayModes( i ); n++)
			{
				SDL_DisplayMode dm;
				SDL_GetDisplayMode( i , n , &dm );
				std::cout << "Display Mode : " << n << std::endl;
				std::cout << "Display Resolution : " << dm.w << 'x' << dm.h << std::endl;
				std::cout << "Display Refresh : " << dm.refresh_rate << std::endl;
				switch (dm.format)
				{
					case (SDL_PIXELFORMAT_RGB888):
						std::cout << "Desktop Display Format : RGB-888" << std::endl;
						break;
					case (SDL_PIXELFORMAT_RGB565):
						std::cout << "Desktop Display Format : RGB-565" << std::endl;
						break;
					default:
						std::cout << "Desktop Display Format : " << dm.format << std::endl;
						break;
				}
				std::cout << std::endl;
			}
#endif
			std::cout << std::endl;

		}

		//Video Drivers
		std::cout << "Current Video Driver : " << SDL_GetCurrentVideoDriver() << std::endl;
		int vid_drivers = SDL_GetNumVideoDrivers();
		for (int n =0; n < vid_drivers; n++)
		{
			std::cout << "Available Video Driver "  << n << " : " << SDL_GetVideoDriver(n) << std::endl;
		}

		std::cout << std::endl;

		//Joystick and Game Controller
		int num_joy;
		num_joy = SDL_NumJoysticks();
		std::cout << num_joy << " JoyStick(s) found" << std::endl;
		for(int i = 0; i < num_joy; i++)
		{
			SDL_Joystick *joystick = SDL_JoystickOpen(i);
			std::cout << "Name:" << SDL_JoystickName(joystick) << std::endl;
			std::cout << "JoyStick Name:" << SDL_JoystickNameForIndex(i) << std::endl;
			std::cout << "Is Game Controller : " << SDL_IsGameController(i) << std::endl;
			std::cout << "Number of Axes : " << SDL_JoystickNumAxes(joystick) << std::endl;
			std::cout << "Number of Buttons : " << SDL_JoystickNumButtons(joystick) << std::endl;
			std::cout << "Number of Balls : " << SDL_JoystickNumBalls(joystick) << std::endl;
			std::cout << "Number of Hats : " << SDL_JoystickNumHats(joystick) << std::endl;

			SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(i);
			std::cout << "GUID:";
			for (int k =0; k < 16; k++)
			{
				std::cout << std::hex << (guid.data[k] + 48);
				if (k % 4 == 0 && k != 0)
				{
					std::cout << "-";
				}
			}
			std::cout << std::dec << std::endl;

			SDL_JoystickClose(joystick);
			if ( SDL_IsGameController(i) == SDL_TRUE )
			{
				std::cout << "Controller Type : " << SDL_GameControllerNameForIndex(i) << std::endl;
			}

		}

		std::cout << std::endl;

		//Audio Drivers
		std::cout << "Audio Drivers" << std::endl;
		std::cout << "Current Audio Drivers : " << SDL_GetCurrentAudioDriver() << std::endl;
		int audio = SDL_GetNumAudioDrivers();
		for (int i = 0; i < audio; i++)
		{
			std::cout << "Audio Driver " <<  i << " : " << SDL_GetAudioDriver(i) << std::endl;
		}

		std::cout << std::endl;

		//Audio Devices
		std::cout << "Audio Devices" << std::endl;
		int count = SDL_GetNumAudioDevices(0);
		for (int i = 0; i < count; i++ )
		{
			std::cout << "Audio device " <<  i << " : " << SDL_GetAudioDeviceName(i, 0) << std::endl;
		}
	}

} /* namespace etc */
