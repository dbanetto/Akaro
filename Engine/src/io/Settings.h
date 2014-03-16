/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/

#ifndef SETTINGS_H_
#define SETTINGS_H_

#pragma once

#include <fstream>
#include <map>
#include <vector>
#include <string>

//A static path to the file
#define SETTINGS_PATH "settings.ini"

namespace IO
{

	/**
	 * @brief A Flag to describe how duplicate are handled . Either ignored new settings or override the old ones
	 */
	enum SettingsDuplicateFlags
	{
		SETTINGS_DUPLICATES_INGORED = 0
									  ,SETTINGS_DUPLICATES_OVERRIDE = 1
	};

	/**
	 * @brief A Flag to describe which search method is used in loading of files
	 */
	enum SettingsLoadFlags
	{
		/**
		 * @brief Do not load properties when it is not loaded and requested
		 */
		SETTING_LOAD_NOTHING = 0    //!< SETTING_LOAD_NOTHING
							   /**
							    * @brief Do load properties when it is not loaded and requested
							    */
							   ,SETTING_LOAD_ON_REQUEST = 1//!< SETTING_LOAD_ON_REQUEST
	};

// SettingsList which is a map of string, string
	typedef  std::map< std::string , std::string >           SettingsMap;
// SettingsList Iterator
	typedef  std::map< std::string , std::string >::iterator SettingsMapIter;

	struct INISection
	{
		std::string header_name;
		SettingsMap properties;
		int start_index;
		int end_index;

		bool loaded;
	};

	typedef  std::map< std::string , INISection >::iterator  INISectionIter;

	/**
	 * @brief A collection of settings loaded from files
	 * @warning Cannot handle same name sections from different files
	 */
	class Settings
	{
		public:
			Settings();
			Settings(SettingsLoadFlags flag);
			virtual ~Settings();

			//Clear stored settings
			void clear();

			// Load all the settings in the file
			void load ( std::string  file , SettingsDuplicateFlags flag);

			void load_section (std::string header , SettingsDuplicateFlags flag);
			void unload_section (std::string header);
			void unload();
			bool exists (std::string header , std::string  key);
			bool exists (std::string header);

			bool get (std::string header , std::string  key , std::string* out);

			bool getBool (std::string header ,  std::string  key , bool* out);

			bool getInt (std::string header , std::string  key , int* out);

			virtual bool add (std::string header , std::string key , std::string value);

			//Implies overriding is OK
			virtual bool set (std::string header , std::string key , std::string value);

			bool save ();

			std::map<std::string,INISection>* getStoredSettings ();

		private:
			std::map<std::string , INISection > stored_settings;

			SettingsLoadFlags loading_flag;
			std::string file_name;

	};
}

#endif
