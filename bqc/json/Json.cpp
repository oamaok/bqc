#include "json/Json.h"
#include "util/Util.h"

Json::JsonType Json::typeOf(const std::string path, const std::string key)
{

}

cJSON* Json::loadJson(const std::string path)
{
	auto search = Json::rootNodes.find(path);
	if(search == Json::rootNodes.end())
	{
		cJSON* rootNode = cJSON_Parse(util::readFile(path).c_str());
		Json::rootNodes[path].reset(rootNode, cJSON_Delete);
		return rootNode;
	}

	return search->second.get();
}

cJSON* Json::findNode(const std::string path, std::string key)
{
	// load the root node for path
	cJSON* currentNode = Json::loadJson(path);
	bool canExit = false;
	int delimeterPos;
	while(!canExit)
	{
		// check for delimeters
		if((delimeterPos = key.find(".")) == std::string::npos)
			canExit = true;
		int size = cJSON_GetArraySize(currentNode);
		
		for(int i = 0; i < size; i++)
		{
			cJSON* item = cJSON_GetArrayItem(currentNode, i);
			if(strcmp(item->string, key.substr(0, delimeterPos).c_str()) == 0)
			{
				currentNode = item;
				if(canExit)
					return currentNode;
				break;
			}
		}
		key = key.substr(delimeterPos + 1);
	}

	return nullptr;
}

int Json::getLength(std::string path, std::string key)
{
	cJSON* node = Json::findNode(path, key);
	if(node->type != cJSON_Array || node->type != cJSON_Object)
		return 0;
	return cJSON_GetArraySize(node);
}

std::vector<std::string> Json::getChildren(std::string path, std::string key)
{
	cJSON* node = Json::findNode(path, key);
}