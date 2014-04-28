/*
 * AudioManager.cpp
 *
 *  Created on: 8/11/2013
 *      Author: drb
 */

#include "AudioManager.h"
#include <iostream>
#include "../etc/string.h"
#include "../io/file.h"
namespace audio
{
	void music_callback( void* data, unsigned char* dev, int num );

	AudioManager::AudioManager ()
	{
		this->device_id = 0;
		this->volume =  100;
	}

	AudioManager::AudioManager ( IO::Settings* audio )
	{
		load_settings( audio );
	}

	AudioManager::~AudioManager ()
	{
		Mix_HaltMusic();
		Mix_CloseAudio();

		this->unloadall();

		Mix_Quit();
	}

	void AudioManager::load_settings( IO::Settings* settings )
	{

		int freq = 44100;
		int channels = 2;
		int chuncksize = 4096;
		std::string device;
		//Load Battery Settings
		settings->load_section( "audio" , IO::SETTINGS_DUPLICATES_INGORED );

		if ( settings->exists( "audio" , "channels" ) )
		{
			settings->getInt( "audio" , "channels" , &channels );
		}

		if ( settings->exists( "audio" , "chuncksize" ) )
		{
			settings->getInt( "audio" , "chuncksize" , &channels );
		}

		if ( settings->exists( "audio" , "volume" ) )
		{
			settings->getInt( "audio" , "volume" , &this->volume );
		}

		if ( settings->exists( "audio" , "device" ) )
		{
			int index;
			if ( settings->getInt( "audio" , "device" , &index ) == true )
			{
				device = SDL_GetAudioDeviceName( index , 0 );
			}
			else
			{
				settings->get( "audio" , "device" , &device );
			}
		}
		else
		{
			device = SDL_GetAudioDeviceName( 0 , 0 );
		}

		//Base Path for all audio files
		if ( settings->exists( "audio" , "path" ) )
		{
			settings->get( "audio" , "path" , &( this->path ) );
			//Add a ending separator
			if ( etc::endswith( path , "/" ) == false && etc::endswith( path , "\\" ) == false )
			{
				//Add platform specific ending
				path += PATH_SEP;
			}
		}
		else
		{
			std::cout << "WARNING : Audio path is not set" << std::endl;
		}

		SDL_AudioSpec want, have;

		SDL_zero( want );
		want.freq = freq;
		want.format = AUDIO_S16;
		want.channels = channels;
		want.samples = chuncksize;
		want.callback = music_callback;  // you wrote this function elsewhere.

		device_id = SDL_OpenAudioDevice( device.c_str()
										 , 0
										 , &want
										 , &have
										 , SDL_AUDIO_ALLOW_FORMAT_CHANGE );
		if ( device_id == 0 )
		{
			std::cout << "Failed to open audio: " << device << std::endl;
		}
		else
		{
			if (std::string(SDL_GetError()) != "")
			{
				std::cout << "Warning from creating Audio Device" << SDL_GetError() << std::endl;
			}
			if ( have.format != want.format ) // we let this one thing change.
				std::cout << "Format changed to " << have.format << std::endl;

			if ( have.channels != want.channels ) // we let this one thing change.
				std::cout << "Channels changed to " << have.channels << std::endl;

			if ( have.samples != want.samples ) // we let this one thing change.
				std::cout << "Samples changed to " << have.samples << std::endl;
		}

		SDL_CloseAudioDevice(device_id);
		if (Mix_OpenAudio( freq , have.format , channels , chuncksize ) == -1)
		{
			std::cout << "Failed to open audio " << SDL_GetError() << std::endl;
		}

		Mix_VolumeMusic( this->volume );
	}

	void AudioManager::setPath ( std::string Path )
	{
		this->path = Path;
	}

	void AudioManager::play ( std::string name )
	{
		Mix_PlayMusic( this->sounds[name] , 1 );
	}

	bool AudioManager::load ( std::string name , std::string file )
	{
		return this->load ( name , file , true );
	}

	bool AudioManager::load ( std::string name , std::string file , bool use_base_path )
	{
		if ( this->exist( name ) == true )
		{
			return false;
		}
		if ( use_base_path )
		{
			file = this->path + file;
		}

		Mix_Music* music = Mix_LoadMUS( file.c_str() );
		if ( music == nullptr )
		{
			return false;
		}

		this->sounds[name] = music;

		return true;
	}

	bool AudioManager::exist ( std::string name )
	{
		if ( this->sounds.find( name ) == this->sounds.end() )
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void AudioManager::unload ( std::string name )
	{
		Mix_FreeMusic ( this->sounds[name] );
		this->sounds.erase( name );
	}

	void AudioManager::unloadall ()
	{
		for ( const auto sfx : this->sounds )
		{
			Mix_FreeMusic( sfx.second );
		}
		this->sounds.clear();
	}

	void music_callback( void* data, unsigned char* dev, int num )
	{

	}

} /* namespace audio */
