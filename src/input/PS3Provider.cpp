/*
 * PS3Provider.cpp
 *
 *  Created on: 17/11/2013
 *      Author: drb
 */

#include "PS3Provider.h"
#include "../etc/string.h"
#include <iostream>

namespace input
{

    ps3bind toPS3Bind (std::string raw)
    {
        ps3bind out;

        std::vector<std::string> codes = etc::split(raw , "+");

        for (auto& code : codes)
        {
            //Button
            if (code[0] == 'B')
            {
                code.erase(code.begin());
                out.buttons.push_back ( (SDL_GameControllerButton) atoi(code.c_str()) );
                continue;
            }
            //Axis
            if (code[0] == 'A')
            {
                code.erase(code.begin());
                bool pos;
                //Axis Positive
                if (code[0] == 'P')
                {
                    pos = true;
                    code.erase(code.begin());
                    out.axis[(SDL_GameControllerAxis) atoi(code.c_str())] = pos;
                    continue;
                }
                //Axis Negative
                if (code[0] == 'N')
                {
                    pos = false;
                    code.erase(code.begin());
                    out.axis[(SDL_GameControllerAxis) atoi(code.c_str())] = pos;
                    continue;
                }
                continue;
            }
        }

        return out;
    }
    std::string PS3BindtoString (ps3bind bind)
    {
        std::string out;

        return out;
    }

    PS3Provider::PS3Provider ()
    {
        this->controller = nullptr;
        this->is_loaded = false;
        this->dead_zone = 1024;

    }

    PS3Provider::~PS3Provider ()
    {
    }

    void PS3Provider::load   (IO::Settings* input_settings)
    {
        this->controller = SDL_GameControllerOpen(0);
        std::cout << "Loaded " << SDL_GameControllerName(this->controller) << " map:" << SDL_GameControllerMapping(this->controller) << std::endl;

        std::map<std::string,IO::INISection>* settings_data =  input_settings->getStoredSettings() ;

        for (auto& header : *settings_data )
        {
            for ( auto& lower : header.second.properties )
            {
                //Check if it is a key
                if ( etc::endswith (lower.first , this->settings_postfix ) )
                {
                    if (this->states[header.first][lower.first] != nullptr)
                        continue;

                    //Add the Key to the local
                    ps3bind* out = new ps3bind;
                    ps3bind k = toPS3Bind(lower.second);
                    out->axis = k.axis;
                    out->buttons = k.buttons;

                    this->states[header.first][lower.first] = out;
                }
            }
        }
        this->is_loaded = true;
    }

    void PS3Provider::unload ()
    {
        SDL_GameControllerClose (this->controller);
        for (auto& header : this->states )
        {
           for ( auto& lower : header.second )
           {
               delete lower.second;
           }
        }
    }

    void PS3Provider::update(const double& delta)
    {

    }

    bool PS3Provider::checkInputState (std::string& header , std::string& name)
    {
        ps3bind* k = this->states[header][name+this->settings_postfix];

        if (k == nullptr)
            return false;

        if (k->buttons.size() < 1 && k->axis.size() < 1)
        {
           std::cout << "ERROR : No Scan codes" << std::endl;
           return false;
        }

        for (auto code : k->axis)
        {
            int diff = SDL_GameControllerGetAxis(this->controller , code.first);

            if (code.second)
            {
                if (diff - dead_zone <= 0)
                {
                    return false;
                }
            } else {
                if (diff + dead_zone >= 0)
                {
                    return false;
                }
            }
        }

        for (auto code : k->buttons)
        {
           if (SDL_GameControllerGetButton(this->controller , code) == false)
           {
               return false;
           }
        }
        return true;
    }
    bool PS3Provider::setInputState (std::string& header , std::string& name, void*& data)
    {
        return false;
    }

} /* namespace input */
