#ifndef CONFIG_H_
#define CONFIG_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

#include "json\cJSON.h"
#include "util.h"

class Config
{
public:
	template <typename T> static T get(std::string key);
private:
	static cJSON* findNode(std::string key);
	static std::unordered_map<std::string, std::shared_ptr<cJSON>> jsonSources;
};


template <typename T> T Config::get(std::string key)
{
	cJSON* node = Config::findNode(key);
	if(node == nullptr)
		return T();
	return util::jsonCast<T>(node);
}

	
#endif