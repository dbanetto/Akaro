/*
 * AudioManager.h
 *
 *  Created on: 8/11/2013
 *      Author: drb
 */

#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#if __GNUC__
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#endif

#include "../io/Settings.h"
#include <string>

namespace audio
{

    class AudioManager
    {
        public:
            AudioManager ();
            AudioManager (IO::Settings* audio_settings);
            virtual  ~AudioManager ();

            void load_settings(IO::Settings* audio_settings);

            void play ();

            void setPath (std::string path);
        private:
            SDL_AudioDeviceID device_id;
            std::string path;
    };

} /* namespace audio */

#endif /* AUDIOMANAGER_H_ */
