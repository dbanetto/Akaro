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
#include <map>

namespace audio
{

    class AudioManager
    {
        public:
            AudioManager ();
            AudioManager (IO::Settings* audio_settings);
            virtual  ~AudioManager ();

            void load_settings(IO::Settings* audio_settings);

            void play (std::string name);
            bool load ( std::string name , std::string file );
            bool load ( std::string name , std::string file , bool use_base_path);
            void unload (std::string name);
            void unloadall ();
            bool exist (std::string name);

            void setPath (std::string path);
        private:
            SDL_AudioDeviceID device_id;
            std::string path;
            std::map <std::string , Mix_Music*> sounds;
    };

} /* namespace audio */

#endif /* AUDIOMANAGER_H_ */
