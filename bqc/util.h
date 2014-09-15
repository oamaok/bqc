#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include "json\parser.h"

namespace util
{
	template <typename T> T jsonCast(JsonValue value);
	template <> int jsonCast<int>(JsonValue value)
	{
		return (int)value.toNumber();
	}
	template <> std::string jsonCast<std::string>(JsonValue value)
	{
		return std::string(value.toString());
	}
	template <> bool jsonCast<bool>(JsonValue value)
	{
		return value.toBool();
	}
	template <> float jsonCast<float>(JsonValue value)
	{
		return (float)value.toNumber();
	}
	template <> double jsonCast<double>(JsonValue value)
	{
		return value.toNumber();
	}
}


#endif