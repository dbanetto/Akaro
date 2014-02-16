/*
 * InputManager.cpp
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#include "InputManager.h"
#include <iostream>

namespace input
{

	InputManager::InputManager ()
	{

	}

	InputManager::~InputManager ()
	{
		for (auto& obj : this->providers)
		{
			if (obj.second->is_loaded)
			{
				obj.second->unload();
			}
			delete obj.second;
		}
	}

	bool InputManager::add_provider (std::string provider_name , InputProvider* provider)
	{
		if (this->exists(provider_name) == false)
		{
			this->providers[provider_name] = provider;
			this->providers[provider_name]->load( &this->input );
			return true;
		}
		else
		{
			return false;
		}
	}
	bool InputManager::remove_provider (std::string provider)
	{
		if (this->exists(provider) == true)
		{
			this->providers.erase(provider);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool InputManager::exists (std::string provider_name)
	{
		if (this->providers.find(provider_name) == this->providers.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool InputManager::checkInput (std::string header , std::string name)
	{
		if (this->input.exists(header) == false)
		{
			std::cout << header << " does not exist" << std::endl;
			return false;
		}

		for (auto pro : this->providers)
		{
			if (pro.second != nullptr)
			{
				if (pro.second->checkInputState(header , name) == true)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool InputManager::checkInput (std::string provider_name , std::string header , std::string name)
	{
		if (this->exists(provider_name) && this->providers[provider_name] != nullptr)
		{
			return this->providers[provider_name]->checkInputState(header , name);
		}
		else
		{
			return false;
		}
	}

	bool InputManager::setInput (std::string provider_name ,std::string header , std::string name , void* data)
	{
		if (this->exists(provider_name))
		{
			return this->providers[provider_name]->setInputState( header , name , data);
		}
		else
		{
			return false;
		}
	}

	bool InputManager::load (std::string settigs_path , IO::SettingsDuplicateFlags dupflags , IO::SettingsLoadFlags loadflags)
	{
		this->input = IO::Settings(loadflags);
		this->input.load( settigs_path , dupflags );

		for (auto& header : *this->input.getStoredSettings() )
		{
			this->input.load_section(header.first , dupflags);
		}
		return true;
	}

	void InputManager::update(const double& delta)
	{
		for (auto& pro : this->providers)
		{
			pro.second->update(delta);
		}
	}
} /* namespace input */
