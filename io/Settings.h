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



/// <summary>
/// A Flag to describe how duplicate are handled
/// Either ignored new settings or override the old ones.
/// </summary>
enum SettingsDuplicateFlags {
    SETTINGS_DUPLICATES_INGORED = 0
   ,SETTINGS_DUPLICATES_OVERRIDE = 1
};

/// <summary>
/// A Flag to describe which search method is used in split()
/// </summary>
enum SettingsLoadFlags {
    /// <summary>
    /// Do not load properties when it is not loaded and requested
    /// </summary>
    SETTING_LOAD_NOTHING = 0
    /// <summary>
    /// Do load properties when it is not loaded and requested 
    /// </summary>
    ,SETTING_LOAD_ON_REQUEST = 1
};

// SettingsList which is a map of string, string
typedef  std::map< std::string , std::string >           SettingsMap;
// SettingsList Iterator
typedef  std::map< std::string , std::string >::iterator SettingsMapIter;

struct INISection  
{
    std::string header_name;
    SettingsMap properties;
    std::string file_name;
    int start_index;
    int end_index;

    bool loaded;
};

typedef  std::map< std::string , INISection >::iterator  INISectionIter;

/* TODO: Add Saving support
 */

/// <summary>
/// A collection of settings loaded from files
/// </summary>
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

        bool exists (std::string header , std::string  key);
        bool exists (std::string header);

        bool get (std::string header , std::string  key , std::string* out);

        bool getBool (std::string header ,  std::string  key , bool* out);

        bool getInt (std::string header , std::string  key , int* out);

        virtual bool add (std::string header , std::string key , std::string value);

        //Implies overriding is OK
        virtual void set (std::string header , std::string key , std::string value);

    private:
        std::map<std::string , INISection > stored_settings;
        SettingsLoadFlags loading_flag;

    };
}

#endif
