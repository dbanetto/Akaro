/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include "Settings.h"

#include <iosfwd>
#include <iostream>

using namespace IO;

#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "../etc/string.h"


Settings::Settings() {
    this->loading_flag = SETTING_LOAD_NOTHING;
}

Settings::Settings(SettingsLoadFlags flag)
{
    this->loading_flag = flag;
}

Settings::~Settings()
{
    this->stored_settings.clear();
}

/**
 * @brief removes all currently loaded settings
 */
void Settings::clear()
{
    this->stored_settings.clear();
}

/**
 * @brief Checks if a given setting exists, and loads it if flags permit
 * @param header section header
 * @param key name of the setting to be accessed
 * @return true on exists
 */
bool Settings::exists (std::string header ,std::string  key)
{
    if (this->exists(header)) 
    {
        INISection* section = &(this->stored_settings[header]);
        if (section->loaded) {
            return section->properties.find(key) != section->properties.end();
        } else {
            //Load Header's properties?
            if ( this->loading_flag == SETTING_LOAD_ON_REQUEST ) {
                this->load_section ( header , SETTINGS_DUPLICATES_INGORED );
                return this->exists ( header , key);
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
}

/**
 * @brief Checks if a header exits
 * @param header Name of section
 * @return true on success
 */
bool Settings::exists (std::string header) 
{
    return this->stored_settings.find(header) != this->stored_settings.end();
}

/**
 * @brief Loads settings from a file
 * @param file_name
 * @param flag
 */
void Settings::load(std::string file_name , SettingsDuplicateFlags flag)
{
    std::fstream file;
    file.open(file_name.c_str());
    
    //Check if the file is open
    if (!(file.is_open()))
    {
        return;
    }

    //Seek to the beginning of the file
    file.seekg( 0 , file.beg );
    file.peek();

    //Calculate the offset from the 1st byte to the 0th element
    int sys_error = file.tellg();

    std::string line;
    INISection section;
    section.file_name = file_name;
    section.header_name = "";
    section.loaded = false;
    section.start_index = 0;

    while ( ! file.eof() )
    {
        //Get current position with the sys error offset
        int start_pos = (int)(file.tellg()) - sys_error;
        std::getline( file , line );

        if (line.length() == 0)
            continue;

        line = etc::trim(line);

        //Treat lines starting with ; as comments and do not process
        if ( etc::startswith( line , ";" ) )
        {
            continue;
        }
        //Check if the line has the beginning of a section
        if (etc::startswith( line , "[" ) && etc::endswith( line , "]" ))
        {
            //Close last section
            section.end_index = (int)file.tellg();
            this->stored_settings[section.header_name] = section;

            //Refresh section
            section = INISection();
            //Remove the brackets
            section.header_name = line.substr ( 1 , line.size() - 2 );
            //-2 constant is to correct the position of the start index
            section.start_index = start_pos;
            section.loaded = false;
            section.file_name = file_name;
            section.properties = SettingsMap();
            continue;
        }

        //Include other files
        if (line[0] == '@')
        {
               //Check if key is @inlcude
            if ( etc::trim ( line.substr( 0 , line.find_first_of('=', 0) ) ) == "@include")
            {
                //Include another file
                //Get file name from the value

                //@include disabled
                // this->load ( etc::trim ( line.substr( line.find_first_of('=', 0) + 1  , line.length() - 1 ) ) , flag );
                continue;
            }
        }
    }

    file.seekg (0 , file.end);
    section.end_index = (int)file.tellg() - sys_error;
    this->stored_settings[section.header_name] = section;

    file.close();
}

/**
 * @brief Loads a section's data into memory
 * @param header Section name
 * @param flag Settings Duplicate Flags
 */
void Settings::load_section ( std::string header , SettingsDuplicateFlags flag) {
    std::fstream file;

    if (this->exists(header) == false)
        return;

    INISection* section = &(this->stored_settings[header]);

    file.open( section->file_name.c_str() );
    int file_pos_max = section->end_index;
    //Check if the file is open
    if (!(file.is_open()))
    {
        return;
    }

    //Seek to the beginning of the file
    file.seekg( 0 , file.beg );
    file.seekg( section->start_index , file.beg );

    while ( file.tellg() < file_pos_max && !file.eof() )
    {
        std::string line;
        std::getline ( file, line );
        line = etc::trim ( line );
        
        if (line == "")
        {
            continue;
        }
        if ( etc::startswith( line , ";" ) )
        {
            continue;
        }
        //Check if the line has the beginning of a section
        if ( etc::startswith( line , "[" ) || etc::endswith( line , "]") )
        {
            continue;
        }
        if ( etc::startswith( line , "@" ) )
        {
            continue;
        }

        
        //Find the equal part of the line
        std::size_t equal_pos = line.find_first_of('=', 0);

        std::string key = etc::trim ( line.substr( 0 , equal_pos ) );
        std::string value = etc::trim ( line.substr( equal_pos + 1  , line.length() - 1 ) );

        

        if ( section->properties.find( key ) !=  section->properties.end() )
        {
            //There is another copy of the key, check if it is OK to override
            if (flag == SETTINGS_DUPLICATES_OVERRIDE)
            {
                section->properties[key] = value;
            }
        }
        else
        {
            section->properties[key] = value;
        }
    }
    //Update loaded status
    section->loaded = true;
    file.close();

}

/**
 * @brief Unloads a specified section
 * @param header a section name
 */
void Settings::unload_section (std::string header) 
{
    if (this->exists(header)) {
        this->stored_settings[header].properties.clear();
        this->stored_settings[header].loaded = false;
    }
}

/**
 * @brief Gets the string of the given setting and copies it into the out string
 * @param header the name of the section
 * @param key the name of setting
 * @param out A string to be written to
 * @return true on successful copy
 */
bool Settings::get (std::string header , std::string  key, std::string* out)
{
    if (this->exists(header ,key))
    {
        *out = this->stored_settings[header].properties[key];
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Gets the value and converts it to a bool
 * @see Settings::get
 * @param bol Returns the value
 * @return
 */
bool Settings::getBool (std::string header , std::string  key , bool* bol)
{
    std::string b;
    if (this->get(header, key , &b) == false)
        return false;
    b = etc::toLower(b);
    if (b != "")
    {
        *bol = ( b == "true" ? true : false );
        return true;
    }
    else
    {
        return false;
    }
}

bool Settings::getInt (std::string header , std::string  key , int* num)
{
    std::string b;
    if (this->get(header, key , &b) == false)
        return false;

    if ( etc::is_number(b) )
    {
        *num = atoi( b.c_str() );
        return true;
    }
    else
    {
        return false;
    }
}

bool Settings::add (std::string header , std::string key , std::string value)
{
    if (!this->exists(header , key))
    {
        this->stored_settings[header].properties[key] = value;
        return true;
    }
    else
    {
        return false;
    }
}

void Settings::set (std::string header , std::string key , std::string value)
{
     if (this->exists( header , key ) ) {
        this->stored_settings[header].properties[key] = value;
     }
}
