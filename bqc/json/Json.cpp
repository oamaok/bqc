#include "json/Json.h"
#include "util/Util.h"
#include "util/Log.h"

std::unordered_map<std::string, std::shared_ptr<cJSON>> Json::rootNodes;

Json::JsonType Json::typeOf(const std::string& path, std::string key)
{
	return Json::JsonType::TYPE_NULL;
}

cJSON* Json::loadJson(const std::string& path)
{
	auto search = Json::rootNodes.find(path);
	if(search == Json::rootNodes.end())
	{
		std::string fileContents = util::readFile(path);
		cJSON* rootNode = cJSON_Parse(fileContents.c_str());
		if(!rootNode)
		{
			const char* errptr = cJSON_GetErrorPtr();
			int line = std::count(fileContents.c_str(), errptr, '\n') + 1;
			Log::error("Failed to parse JSON %s:%d.", path.c_str(), line);
			return nullptr;
		}

		Json::rootNodes[path].reset(rootNode, cJSON_Delete);
		return rootNode;
	}

	return search->second.get();
}



cJSON* Json::findNode(const std::string& path, std::string key)
{
	// load the root node for path
	cJSON* currentNode = Json::loadJson(path);

	// empty key: return root node
	if(key.length() == 0)
		return currentNode;

	bool canExit = false;
	int delimeterPos;
	while(!canExit)
	{
		// check for delimeters; if none found, function is ready to exit
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

int Json::getLength(const std::string& path, std::string key)
{
	cJSON* node = Json::findNode(path, key);
	if(node->type != cJSON_Array || node->type != cJSON_Object)
		return 0;
	return cJSON_GetArraySize(node);
}

std::vector<std::string> Json::getChildNames(const std::string& path, std::string key)
{
	cJSON* node = Json::findNode(path, key);
	int size = cJSON_GetArraySize(node);
	
	std::vector<std::string> ret;

	for(int i = 0; i < size; i++)
	{
		cJSON* item = cJSON_GetArrayItem(node, i);
		ret.push_back(item->string);
	}

	return ret;
}

std::vector<cJSON*> Json::getChildren(const std::string& path, std::string key)
{
	cJSON* node = Json::findNode(path, key);

	int size = cJSON_GetArraySize(node);
	
	std::vector<cJSON*> ret;

	for(int i = 0; i < size; i++)
	{
		cJSON* item = cJSON_GetArrayItem(node, i);
		ret.push_back(item);
	}

	return ret;
}