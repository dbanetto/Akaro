/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include "Settings.h"

using namespace IO;

#include <stdlib.h>
#include <string.h>
#ifdef SETTINGS_REGEX_ENABLED
#include <regex>
#endif

static const std::string& whitespace = " \t\0";

std::string trim (std::string str);
bool endswith (std::string str,std::string  suffix);
bool startswith (std::string str,std::string  prefix);
std::string toLower (std::string str);
char tolower(char in);

Settings::Settings() {
    this->loading_flag = SETTING_LOAD_NOTHING;
}

Settings::Settings(SettingsLoadFlags flag)
{
    // TODO Auto-generated constructor stub
    this->loading_flag = flag;
}

Settings::~Settings()
{
    // TODO Auto-generated destructor stub
    this->stored_settings.clear();
}

void Settings::clear()
{
    this->stored_settings.clear();
}

bool Settings::exists (std::string header ,std::string  setting)
{
    if (this->exists(header)) 
    {
        if (this->stored_settings[header].loaded) {
            if ( this->stored_settings[header].properties.find(setting) == this->stored_settings[header].properties.end() ) {
                return false;
            } else {
                return true;
            }
        } else {
            //Load Header's properties?
            if ( this->loading_flag == SETTING_LOAD_ON_REQUEST ) {
                this->load_section ( header , SETTINGS_DUPLICATES_INGORED );
                return this->exists ( header , setting);
            }
            return false;
        }
    } else {
        return false;
    }
}

bool Settings::exists (std::string header) 
{
    if(this->stored_settings.find(header) == this->stored_settings.end() )
    {
        return false;
    } else {
        return true;
    }
}


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
    std::string line;
    INISection section;
    section.file_name = file_name;
    section.header_name = "";
    section.loaded = false;
    section.start_index = 0;

    while ( ! file.eof() )
    {
        //Get the current line
        int start_pos = file.tellg();
        std::getline ( file, line );
        if (line.length() == 0)
            continue;
        line = trim(line);

        //Treat lines starting with ; as comments and do not process
        if (line[0] == ';')
        {
            continue;
        }
        //Check if the line has the beginning of a section
        if (line[0] == '[' && line[line.size() - 1] == ']')
        {
            
            //Close last section
            section.end_index = start_pos;
            this->stored_settings[section.header_name] = section;
            
            //Refresh section
            section = INISection();
            //Remove the brackets
            section.header_name = line.substr ( 1 , line.size() - 2 );
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
            if ( trim ( line.substr( 0 , line.find_first_of('=', 0) ) ) == "@include")
            {
                //Include another file
                //Get file name from the value
                this->load ( trim ( line.substr( line.find_first_of('=', 0) + 1  , line.length() - 1 ) ) , flag );
                continue;
            }
        }
    }

    file.seekg (0 , file.end);
    section.end_index = file.tellg();
    this->stored_settings[section.header_name] = section;

    file.close();
}

void Settings::load_section ( std::string header , SettingsDuplicateFlags flag) {
    std::fstream file;
    file.open( this->stored_settings[header].file_name.c_str() );
    int file_pos_max = this->stored_settings[header].end_index;
    //Check if the file is open
    if (!(file.is_open()))
    {
        return;
    }

    //Seek to the beginning of the file
    file.seekg( this->stored_settings[header].start_index , file.beg );
    std::string line;
    while ( file.tellg() <  file_pos_max && !file.eof() )
    {
        std::getline ( file, line );
        line = trim ( line );
        
        if (line == "")
        {
            continue;
        }
        if (line[0] == ';')
        {
            continue;
        }
        //Check if the line has the beginning of a section
        if (line[0] == '[')
        {
            continue;
        }
        if (line[0] == '@')
        {
            continue;
        }

        
        //Find the equal part of the line
        std::size_t equal_pos = line.find_first_of('=', 0);

        std::string key = trim ( line.substr( 0 , equal_pos ) );
        std::string value = trim ( line.substr( equal_pos + 1  , line.length() - 1 ) );

        

        if (this->stored_settings[header].properties.count( key ) > 0 )
        {
            //There is another copy of the key, check if it is OK to override
            if (flag == SETTINGS_DUPLICATES_OVERRIDE)
            {
                this->stored_settings[header].properties[key] = value;
            }
        }
        else
        {
            this->stored_settings[header].properties[key] = value;
        }
    }
    //Update loaded status
    this->stored_settings[header].loaded = true;
}

void Settings::unload_section (std::string header) 
{
    if (this->exists(header)) {
        this->stored_settings[header].properties.clear();
        this->stored_settings[header].loaded = false;
    }
}

std::string Settings::get (std::string header , std::string  setting)
{
    if (this->exists(header ,setting))
    {
        return this->stored_settings[header].properties[setting];
    }
    else
    {
        return "";
    }
}

bool  Settings::getBool (std::string header , std::string  key)
{
    std::string b = this->get(header, key);
    if (b != "")
    {
        return  ( b == "true" ? true : false );
    }
    else
    {
        return false;
    }
}

int Settings::getInt (std::string header , std::string  key)
{
    std::string b = this->get(header,key);
    if (b != "")
    {
        return atoi( this->get(header,key).c_str() );
    }
    else
    {
        return -1;
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

std::string trim (std::string str)
{
    //Remove trailing whitespace
    int strBegin = str.find_first_not_of(whitespace);
    int strEnd = str.find_last_not_of(whitespace);
    
    if (str == "") {
        return "";
    }

    return str.substr(strBegin,  strEnd - strBegin + 1);
}

bool endswith (std::string str,std::string  suffix)
{
    if( str == "" || suffix == "" )
        return false;

    if(suffix.length() > str.length())
        return false;

    return 0 == strncmp( str.c_str() + str.length() - suffix.length(), suffix.c_str() , suffix.length() );
}
bool startswith (std::string str,std::string  prefix)
{
    if( str == "" || prefix == "" )
        return false;

    if(prefix.length() > str.length())
        return false;

    return 0 == strncmp( str.c_str(), prefix.c_str() , prefix.length() );
}

std::string toLower (std::string str) 
{
    for ( unsigned int i = 0; i < str.size(); i++ ) {
        if(str[i]<='Z' && str[i]>='A') {
            str[i] =  tolower(str[i]);
        }
    }
    return str;
}

char tolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
} 
