#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>
#include "json\parser.h"
#include "util.h"
#include <iostream>
#include <fstream>

class Config
{
public:
	template <typename T> static T get(std::string key);
private:
	static std::unordered_map<std::string, JsonValue> jsonSources;
};

#endif