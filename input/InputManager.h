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

namespace input
{

    class InputManager
    {
        public:
            InputManager();
            InputManager(std::string settigs_path);
            virtual ~InputManager();

            bool load (std::string settigs_path);

            //Provider Management
            bool add_provider (std::string provider_name , InputProvider* provider);
            bool remove_provider (std::string provider);
            bool exists (std::string provider_name);

        private:
            std::map<std::string , InputProvider*> providers;
            IO::Settings input;
    };

} /* namespace input */

#endif /* INPUTMANAGER_H_ */
