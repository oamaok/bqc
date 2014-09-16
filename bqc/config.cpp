#include "config.h"

std::unordered_map<std::string, cJSON*> Config::jsonSources = std::unordered_map<std::string, cJSON*>();


cJSON* Config::findNode(std::string key)
{
	int delimeterPos = key.find(".");
	std::string filename = "cfg/" + key.substr(0, delimeterPos) + ".json";
	key = key.substr(delimeterPos + 1);

	auto search = Config::jsonSources.find(filename);
	if(search == Config::jsonSources.end())
	{
		cJSON* rootNode = cJSON_Parse(util::readFile(filename).c_str());
		Config::jsonSources[filename] = rootNode;
		search = Config::jsonSources.find(filename);
	}

	cJSON* currentNode = search->second;
	bool returnValue = false;
	while(!returnValue)
	{
		if((delimeterPos = key.find(".")) == std::string::npos)
			returnValue = true;
		int size = cJSON_GetArraySize(currentNode);
		for(int i = 0; i < size; i++)
		{
			cJSON* item = cJSON_GetArrayItem(currentNode, i);
			if(strcmp(item->string, key.substr(0, delimeterPos).c_str()) == 0)
			{
				currentNode = item;
				if(returnValue)
					return currentNode;
				break;
			}
		}
		key = key.substr(delimeterPos + 1);
	}

	return nullptr;
}