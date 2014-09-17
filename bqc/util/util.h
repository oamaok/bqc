#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include "json/cJSON.h"

namespace util
{
	template <typename T> T jsonCast(cJSON* value);
	template <> int jsonCast<int>(cJSON* value);
	template <> std::string jsonCast<std::string>(cJSON* value);
	template <> bool jsonCast<bool>(cJSON* value);
	template <> float jsonCast<float>(cJSON* value);
	template <> double jsonCast<double>(cJSON* value);

	std::string readFile(const std::string& path);
}


#endif