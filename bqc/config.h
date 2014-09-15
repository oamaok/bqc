#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>
#include "json\parser.h"

class Config
{
public:
	template<typename T> static T get(std::string key);
private:
	std::unordered_map<std::string, JsonValue> jsonSources;
};

#endif