/*
 * AudioManager.cpp
 *
 *  Created on: 8/11/2013
 *      Author: drb
 */

#include "AudioManager.h"
#include <iostream>

namespace audio
{
    void music_callback(void* data, unsigned char* dev, int num);

    AudioManager::AudioManager ()
    {
        // TODO Auto-generated constructor stub
    }

    AudioManager::AudioManager (IO::Settings* audio)
    {
        // TODO Auto-generated constructor stub
        load_settings(audio);
    }

    AudioManager::~AudioManager ()
    {
        // TODO Auto-generated destructor stub
    }

    void AudioManager::load_settings(IO::Settings* settings)
    {

        int freq = 44100;
        int channels = 2;
        int chuncksize = 4096;
        std::string device;
        //Load Battery Settings
        settings->load_section( "audio" , IO::SETTINGS_DUPLICATES_INGORED );


        //Set the check interval
        if ( settings->exists("audio" , "freq") )
        {
            settings->getInt("audio" , "freq" , &freq);
        }

        if ( settings->exists("audio" , "channels") )
        {
            settings->getInt("audio" , "channels" , &channels);
        }

        if ( settings->exists("audio" , "chuncksize") )
        {
            settings->getInt("audio" , "chuncksize" , &channels);
        }

        if ( settings->exists("audio" , "device") )
        {
            int index;
            if (settings->getInt("audio" , "device" , &index) == true) {
                device = SDL_GetAudioDeviceName(index , 0);
            } else {
                settings->get("audio" , "device" , &device);
            }
        }

        SDL_AudioSpec want, have;

        SDL_zero(want);
        want.freq = freq;
        want.format = AUDIO_F32;
        want.channels = channels;
        want.samples = chuncksize;
        want.callback = music_callback;  // you wrote this function elsewhere.

        SDL_CloseAudioDevice(1);

        device_id = SDL_OpenAudioDevice(device.c_str() , 0, &want, &have, SDL_AUDIO_ALLOW_ANY_CHANGE);
        if (device_id == 0) {
            std::cout << "Failed to open audio: " << device << " " << SDL_GetError() << std::endl;
        } else {

            std::cout << "Loaded Device : " << device << SDL_GetError() << std::endl;

            if (have.format != want.format)  // we let this one thing change.
               std::cout << "Format changed to " << have.format << std::endl;

            if (have.channels != want.channels)  // we let this one thing change.
               std::cout << "Channels changed to " << have.channels << std::endl;

            if (have.samples != want.samples)  // we let this one thing change.
               std::cout << "Samples changed to " << have.samples << std::endl;
        }

        Mix_OpenAudio( freq , AUDIO_F32 , channels , chuncksize );
    }

    void music_callback(void* data, unsigned char* dev, int num)
    {

    }

} /* namespace audio */
