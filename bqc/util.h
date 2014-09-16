#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include "json\parser.h"

namespace util
{
	template <typename T> T jsonCast(JsonValue value);
	template <> int jsonCast<int>(JsonValue value);
	template <> std::string jsonCast<std::string>(JsonValue value);
	template <> bool jsonCast<bool>(JsonValue value);
	template <> float jsonCast<float>(JsonValue value);
	template <> double jsonCast<double>(JsonValue value);
}


#endif