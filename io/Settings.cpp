/*
    Author : David Barnett
    Date   : 03-10-2013
    License: MIT License
*/
#include "Settings.h"
#include <iostream>
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
bool is_number (std::string s);

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
    	INISection* section = &(this->stored_settings[header]);
        if (section->loaded) {
            return section->properties.find(setting) != section->properties.end();
        } else {
            //Load Header's properties?
            if ( this->loading_flag == SETTING_LOAD_ON_REQUEST ) {
                this->load_section ( header , SETTINGS_DUPLICATES_INGORED );
                return this->exists ( header , setting);
            } else {
            	return false;
            }
        }
    } else {
        return false;
    }
}

bool Settings::exists (std::string header) 
{
	return this->stored_settings.find(header) != this->stored_settings.end();
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

        line = trim(line);

        //Treat lines starting with ; as comments and do not process
        if ( startswith( line , ";" ) )
        {
            continue;
        }
        //Check if the line has the beginning of a section
        if (startswith( line , "[" ) && endswith( line , "]" ))
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
    section.end_index = (int)file.tellg() - sys_error;
    this->stored_settings[section.header_name] = section;

    file.close();
}

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
        line = trim ( line );
        
        if (line == "")
        {
            continue;
        }
        if ( startswith( line , ";" ) )
		{
			continue;
		}
        //Check if the line has the beginning of a section
        if ( startswith( line , "[" ) || endswith( line , "]") )
		{
			continue;
		}
        if ( startswith( line , "@" ) )
        {
            continue;
        }

        
        //Find the equal part of the line
        std::size_t equal_pos = line.find_first_of('=', 0);

        std::string key = trim ( line.substr( 0 , equal_pos ) );
        std::string value = trim ( line.substr( equal_pos + 1  , line.length() - 1 ) );

        

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

void Settings::unload_section (std::string header) 
{
    if (this->exists(header)) {
        this->stored_settings[header].properties.clear();
        this->stored_settings[header].loaded = false;
    }
}

bool Settings::get (std::string header , std::string  setting, std::string* out)
{
    if (this->exists(header ,setting))
    {
    	*out = this->stored_settings[header].properties[setting];
    	return true;
    }
    else
    {
        return false;
    }
}

bool  Settings::getBool (std::string header , std::string  key , bool* bol)
{
    std::string b;
    if (this->get(header, key , &b) == false)
    	return false;
    b = toLower(b);
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

    if ( is_number(b) )
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

bool is_number(const std::string s)
{
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}
