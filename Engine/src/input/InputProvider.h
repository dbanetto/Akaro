/*
 * InputProvider.h
 *
 *  Created on: 14/11/2013
 *      Author: drb
 */

#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_

#include <string>
#include "../io/Settings.h"

namespace input
{

	class InputProvider
	{
		public:
			InputProvider ();
			virtual ~InputProvider ();

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
			const std::string settings_postfix = "";
	};

} /* namespace input */

#endif /* INPUTPROVIDER_H_ */
