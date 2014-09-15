#include "config.h"
#include "util.h"
#include <iostream>
#include <fstream>

template<typename T> static T Config::get(std::string key)
{
	int delimeterPos = key.find(".");
	std::string filename = key.substr(0, delimeterPos);
	key = key.substr(delimeterPos);

	auto search = jsonSources.find(filename);

	if(search != example.end())
	{
		JsonValue value = search->second;
		while((delimeterPos = key.find(".")) != std::string::npos)
		{
			for(auto i : value)
			{
				if(std::string(i->key) == key.substr(0, delimeterPos))
				{
					value = i->value;
				}
			}
		}
		return util::jsonCast<t>(value);
	}
	else
	{
		std::ifstream jsonFile(filename, std::ifstream::binary);

		if(jsonFile)
		{
			jsonFile.seekg(0, jsonFile.end);
			int length = jsonFile.tellg();
			jsonFile.seekg(0, jsonFile.beg);

			char* jsonString = new char[length];

			jsonFile.read(jsonString, length);

			char* endptr;
			JsonValue value;
			JsonAllocator allocator;

			JsonStatus status = jsonParse(jsonString, &endptr, &value, &allocator);

			// TODO: better error handling, for now cause the program to crash
			if(status != JSON_PARSE_OK)
				exit(EXIT_FAILURE);

			jsonSources[filename] = value;
		
			jsonFile.close();
			delete [] jsonString;
		}
	}

}