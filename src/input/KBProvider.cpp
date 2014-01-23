/*
 * KBProvider.cpp
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#include "KBProvider.h"
#include "../etc/string.h"
#include <iostream>

namespace input
{
    Key stringToKeys (std::string keys)
    {
        Key out;

        // #C++11 bitches
        std::vector<std::string> codes = etc::split(keys , "+");

        out.keymod = KMOD_NONE;
        for (auto& code : codes)
        {
            //Check if the code starts with K but not only a K
            if (code[0] == 'K' && code != "K")
            {
                //Pretty sure it is a K-mod now
                code.erase(code.begin());
                out.keymod = (SDL_Keymod)( atoi ( code.c_str() ));
                continue;
            }
            SDL_Scancode sc = SDL_GetScancodeFromName( code.c_str() );
            if (sc == SDL_SCANCODE_UNKNOWN)
            {
                std::cout << code << " is an incorrect SDL_SCANCODE." << std::endl;
            } else {
                out.scan_codes.push_back ( sc );
            }
        }
        return out;
    }
    std::string keysToString (Key key)
    {
        std::string out;

        for (auto& code : key.scan_codes) {
            out += std::string(SDL_GetScancodeName(code));
        }


        if ((int)(key.keymod) != 0)
        {
            out += "+";
            out += "K" + etc::convInt(key.keymod);
        }

        return out;
    }


    KBProvider::KBProvider ()
    {
        this->key_states = nullptr;
    }

    KBProvider::~KBProvider ()
    {
        unload ();
    }

    void KBProvider::update(const double& delta )
    {
        this->key_states = SDL_GetKeyboardState(NULL);
    }

    void KBProvider::load   (IO::Settings* input_settings)
    {
        std::map<std::string,IO::INISection>* settings_data =  input_settings->getStoredSettings() ;

        for (auto& header : *settings_data )
        {
            for ( auto& lower : header.second.properties )
            {
                //Check if it is a key
                if ( etc::endswith (lower.first , this->settings_postfix ) )
                {
                    if (this->keys[header.first][lower.first] != nullptr)
                        continue;

                    //Add the Key to the local
                    Key* out = new Key;
                    Key k = stringToKeys(lower.second);
                    out->keymod = k.keymod;
                    out->scan_codes = k.scan_codes;

                    this->keys[header.first][lower.first] = out;
                }
            }
        }
        this->is_loaded = true;
    }

    void KBProvider::unload ()
    {
        for (auto& header : this->keys )
       {
           for ( auto& lower : header.second )
           {
               delete lower.second;
           }
           header.second.clear();
       }
        this->keys.clear();
    }

    bool  KBProvider::checkInputState (std::string& header , std::string& name)
    {
        Key* k = this->keys[header][name+this->settings_postfix];

        if (k->keymod != KMOD_NONE)
        {
            if ( (k->keymod & SDL_GetModState()) == false)
            {
                return false;
            }
        }

        if (k->scan_codes.size() < 1)
        {
            std::cout << "ERROR : No Scan codes" << std::endl;
            return false;
        }

        for (auto code : k->scan_codes)
        {
            if (this->key_states[code] == false)
            {
                return false;
            }
        }
        return true;

    }

    bool  KBProvider::setInputState (std::string& header , std::string& name, void*& data)
    {
        return false;
    }

} /* namespace input */
