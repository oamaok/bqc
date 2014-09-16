#include "config.h"

std::unordered_map<std::string, JsonValue> Config::jsonSources = std::unordered_map<std::string, JsonValue>();

template <typename T> T Config::get(std::string key)
{
	int delimeterPos = key.find(".");
	std::string filename = key.substr(0, delimeterPos);
	key = key.substr(delimeterPos);

	auto search = Config::jsonSources.find(filename);

	if(search == Config::jsonSources.end())
	{
		std::ifstream jsonFile("cfg/" + filename + ".json", std::ifstream::binary);

		if(!jsonFile) // couldn't open file
			exit(EXIT_FAILURE);

		jsonFile.seekg(0, jsonFile.end);
		int length = jsonFile.tellg();
		jsonFile.seekg(0, jsonFile.beg);

		char* jsonString = new char[length]; // do NOT free this! intended "memory leak"

		jsonFile.read(jsonString, length);

		char* endptr;
		JsonValue value;
		JsonAllocator allocator;
		
		JsonParseStatus status = jsonParse(jsonString, &endptr, &value, allocator);

		// TODO: better error handling, for now cause the program to crash
		if(status != JSON_PARSE_OK)
			exit(EXIT_FAILURE);

		Config::jsonSources[filename] = value;
		
		jsonFile.close();
		
		search = Config::jsonSources.find(filename);
	}

	JsonValue value = search->second;

	while((delimeterPos = key.find(".")) != std::string::npos)
	{
		for(const auto& i : value)
		{
			if(std::string(i->key) == key.substr(0, delimeterPos))
			{
				value = i->value;
			}
		}
		key = key.substr(delimeterPos, 0);
	}

	return util::jsonCast<T>(value);
}

