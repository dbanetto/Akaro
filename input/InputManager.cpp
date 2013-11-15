/*
 * InputManager.cpp
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#include "InputManager.h"

namespace input
{

    InputManager::InputManager ()
    {
        // TODO Auto-generated constructor stub

    }

    InputManager::~InputManager ()
    {
        // TODO Auto-generated destructor stub
        for (auto& obj : this->providers) {
            if (obj.second->is_loaded) {
                obj.second->unload();
            }
            delete obj.second;
        }
    }

    bool InputManager::add_provider (std::string provider_name , InputProvider* provider)
    {
        if (this->exists(provider_name) == false) {
            this->providers[provider_name] = provider;
            return true;
        } else {
            return false;
        }
    }
    bool InputManager::remove_provider (std::string provider)
    {
        if (this->exists(provider) == true) {
            this->providers.erase(provider);
            return true;
        } else {
            return false;
        }
    }
    bool InputManager::exists (std::string provider_name)
    {
        if (this->providers.find(provider_name) == this->providers.end())
        {
            return false;
        } else {
            return true;
        }
    }

} /* namespace input */
