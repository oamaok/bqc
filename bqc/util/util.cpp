#include "util.h"
#include <iostream>
#include <fstream>
namespace util
{
	template <> int jsonCast<int>(cJSON* value)
	{
		if(value->type == cJSON_Number)
			return value->valueint;
		if(value->type == cJSON_String)
			return atoi(value->valuestring);
		if(value->type == cJSON_False)
			return 0;
		if(value->type == cJSON_True)
			return 1;

		return 0;
	}
	template <> std::string jsonCast<std::string>(cJSON* value)
	{
		if(value->type == cJSON_String)
			return std::string(value->valuestring);
		return "";
	}
	template <> bool jsonCast<bool>(cJSON* value)
	{
		if(value->type == cJSON_False || value->type == cJSON_NULL)
			return false;
		if(value->type == cJSON_Object || value->type == cJSON_Array)
			return (bool)cJSON_GetArraySize(value);
		if (value->type == cJSON_Number && value->valueint == 0)
			return false;
		return true;
	}
	template <> float jsonCast<float>(cJSON* value)
	{
		return (float)value->valuedouble;
	}
	template <> double jsonCast<double>(cJSON* value)
	{
		return value->valuedouble;
	}

	std::string readFile(const std::string& path)
	{
		std::ifstream file(path, std::ifstream::binary);

		if(!file) // couldn't open file
		{
			exit(EXIT_FAILURE);
		}
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		std::string buffer(size, '\0');
		file.seekg(0);
		file.read(&buffer[0], size); 

		return buffer;
	}
}

