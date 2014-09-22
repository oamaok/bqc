#ifndef JSON_H_
#define JSON_H_

#include <string>
#include <unordered_map>

#include "json/cJSON.h"

namespace Json
{
	int typeOf(const std::string path, const std::string key);
	cJSON loadJson(const std::string path);
	template <typename T> T get(const std::string path, const std::string key);
	std::string* getChildren(const std::string path, const std::string key);
	int getSize(const std::string path, const std::string key);
	static std::unordered_map<std::string, cJSON> rootNodes;
};


#endif