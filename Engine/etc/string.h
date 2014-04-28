/*
 * string.h
 *
 *  Created on: 7/10/2013
 *      Author: drb
 */

#ifndef STRING_H_
#define STRING_H_

#include <string>
#include <vector>

namespace etc
{

	std::vector<std::string> split (std::string String , std::string token);

//Util Functions
	static const std::string& whitespace = " \t\0";

	std::string trim (std::string str);
	bool endswith (std::string str,std::string  suffix);
	bool startswith (std::string str,std::string  prefix);
	std::string toLower (std::string str);
	char tolower(char in);
	bool is_number (std::string s);

	std::string convInt (int num);

	int timeToInt (std::string time);

}
#endif /* STRING_H_ */
