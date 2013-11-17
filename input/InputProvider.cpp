/*
 * InputProvider.cpp
 *
 *  Created on: 14/11/2013
 *      Author: drb
 */

#include "InputProvider.h"

namespace input
{

    InputProvider::InputProvider ()
    {
        // TODO Auto-generated constructor stub
        this->is_loaded = false;
    }

    InputProvider::~InputProvider ()
    {
        // TODO Auto-generated destructor stub
    }

    void InputProvider::load   (IO::Settings* input_settings)
    {

    }
    void InputProvider::unload ()
    {

    }

    void InputProvider::update(const double& delta)
    {

    }

    bool InputProvider::checkInputState (std::string& header , std::string& name)
    {
        return false;
    }
    bool InputProvider::setInputState (std::string& header , std::string& name, void*& data)
    {
        return false;
    }

} /* namespace input */
