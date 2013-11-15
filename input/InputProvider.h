/*
 * InputProvider.h
 *
 *  Created on: 14/11/2013
 *      Author: drb
 */

#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_

namespace input
{

    class InputProvider
    {
        public:
            InputProvider ();
            virtual ~InputProvider ();

            //Loading and unloading
            virtual void load   ();
            virtual void unload ();

            bool is_loaded;
    };

} /* namespace input */

#endif /* INPUTPROVIDER_H_ */
