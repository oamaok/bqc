#ifndef CONFIG_H_
#define CONFIG_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

#include "json/Json.h"
#include "util.h"

class Config
{
public:
	template <typename T> static T get(std::string key);
};


template <typename T> T Config::get(std::string key)
{
	int delimeterPos = key.find(".");
	std::string file = key.substr(0, delimeterPos);
	key = key.substr(delimeterPos + 1);
	return Json::loadJson("cfg/" + file + ".json")->get<T>(key);
}


	
#endif