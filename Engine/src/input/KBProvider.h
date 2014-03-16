/*
 * KBProvider.h
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#ifndef KBPROVIDER_H_
#define KBPROVIDER_H_

#include "InputProvider.h"

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <string>
#include <vector>
#include <map>

struct Key
{
	std::vector<SDL_Scancode> scan_codes;
	SDL_Keymod  keymod;
};

Key stringToKeys (std::string keys);
std::string keysToString (Key key);

namespace input
{

	class KBProvider : public input::InputProvider
	{
		public:
			KBProvider ();
			virtual ~KBProvider ();

			void load   (IO::Settings* input_settings);
			void unload ();

			void update(const double& delta );

			bool checkInputState (std::string& header , std::string& name);
			bool setInputState (std::string& header , std::string& name, void*& data);
		protected:
			const std::string settings_postfix = ".key";
		private:
			std::map < std::string , std::map <std::string , Key* > > keys;
			const Uint8* key_states;
	};

} /* namespace input */

#endif /* KBPROVIDER_H_ */
