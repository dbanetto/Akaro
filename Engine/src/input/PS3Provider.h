/*
 * PS3Provider.h
 *
 *  Created on: 17/11/2013
 *      Author: drb
 */

#ifndef PS3PROVIDER_H_
#define PS3PROVIDER_H_

#include "InputProvider.h"

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

namespace input
{

	struct ps3bind
	{
		std::vector<SDL_GameControllerButton> buttons;
		//true == positive and false == negative
		std::map<SDL_GameControllerAxis, bool>   axis;
	};

	ps3bind toPS3Bind (std::string raw);
	std::string PS3BindtoString (ps3bind bind);

	class PS3Provider : public input::InputProvider
	{
		public:
			PS3Provider ();
			virtual ~PS3Provider ();

			//Loading and unloading
			virtual void load   (IO::Settings* input_settings);
			virtual void unload ();

			//Check input state, if true then it is active
			virtual bool checkInputState (std::string& header , std::string& name);
			//Change the needed input state
			virtual bool setInputState (std::string& header , std::string& name, void*& data);
			virtual void update(const double& delta);
			bool is_loaded;
		protected:
			const std::string settings_postfix = ".ps3";
		private:
			SDL_GameController* controller;
			int dead_zone;

			std::map <std::string , std::map < std::string , ps3bind* > > states;
	};

} /* namespace input */

#endif /* PS3PROVIDER_H_ */
