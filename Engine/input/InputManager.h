/*
 * InputManager.h
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "InputProvider.h"
#include "../io/Settings.h"

#define INPUT_SETTINGS_FILE "data/input.ini"

namespace input
{

	class InputManager
	{
		public:
			InputManager();
			InputManager( std::string settigs_path );
			virtual ~InputManager();

			bool load ( std::string settigs_path , IO::SettingsDuplicateFlags dupflags , IO::SettingsLoadFlags loadflags );
			void unload();

			//Provider Management
			bool add_provider ( std::string provider_name , InputProvider* provider );
			bool remove_provider ( std::string provider_name );
			bool exists ( std::string provider_name );

			bool checkInput ( std::string header , std::string name );
			bool checkInput ( std::string provider_name , std::string header , std::string name );
			bool setInput ( std::string provider_name , std::string header , std::string name , void* data );

			void update( const double& delta );
		private:
			std::map<std::string , InputProvider*> providers;
			IO::Settings input;
	};

} /* namespace input */

#endif /* INPUTMANAGER_H_ */
