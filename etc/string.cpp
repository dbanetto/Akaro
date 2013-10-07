/*
 * string.cpp
 *
 *  Created on: 7/10/2013
 *      Author: drb
 */

#include "string.h"

#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace etc
{

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

std::vector<std::string> split (std::string String , std::string delimiter)
{
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = String.find(delimiter)) != std::string::npos) {
	    token = String.substr(0, pos);
	    tokens.push_back (token);
	    String.erase(0, pos + delimiter.length());
	}
	return tokens;
}

std::string convInt (int num) {
	std::stringstream ss;//create a stringstream
	ss << num;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

} /* Namespace etc  */
