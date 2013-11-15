/*
 * KBProvider.cpp
 *
 *  Created on: 15/11/2013
 *      Author: drb
 */

#include "KBProvider.h"
#include "../etc/string.h"

namespace input
{

    KBProvider::KBProvider ()
    {
        // TODO Auto-generated constructor stub

    }

    KBProvider::~KBProvider ()
    {
        // TODO Auto-generated destructor stub
    }

    void KBProvider::load   ()
    {

    }
    void KBProvider::unload ()
    {

    }

    Key stringToKeys (std::string keys)
    {
        Key out;

        // #C++11 bitches
        auto codes = etc::split(keys , "+");
        for (auto& code : codes)
        {
            //Check if the code starts with K but not only a K
            if (etc::startswith(code , "K" ) && code != "K")
            {
                //Pretty sure it is a K-mod now
                out.keymod = (SDL_Keymod)( atoi ( code.c_str() ));
                continue;
            }

            out.scan_codes.push_back ( SDL_GetScancodeFromName( code.c_str() ));
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

} /* namespace input */
