#include "json/Json.h"
#include "util/Util.h"
#include "util/Log.h"

Json::Json(const std::string& path)
{
	std::string fileContents = util::readFile(path);
	rootNode = (std::shared_ptr<cJSON>)cJSON_Parse(fileContents.c_str());
	if(!rootNode)
	{
		const char* errptr = cJSON_GetErrorPtr();
		int line = std::count(fileContents.c_str(), errptr, '\n') + 1;
		Log::error("Failed to parse JSON: %s:%d", path.c_str(), line);
	}
}

Json::JsonType Json::typeOf(std::string key)
{
	return Json::JsonType::TYPE_NULL;
}

Json& Json::loadJson(const std::string& path)
{
	auto search = jsonCache.find(path);

	if(search == jsonCache.end())
	{
		Json json(path);
		jsonCache[path] = json;
		return json;
	}
	
	return search->second;
}



cJSON* Json::findNode(std::string key)
{
	// load the root node for path
	cJSON* currentNode = rootNode.get();

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

int Json::getLength(std::string key)
{
	cJSON* node = Json::findNode(key);
	if(node->type != cJSON_Array || node->type != cJSON_Object)
		return 0;
	return cJSON_GetArraySize(node);
}

std::vector<std::string> Json::getChildNames(std::string key)
{
	cJSON* node = Json::findNode(key);
	int size = cJSON_GetArraySize(node);
	
	std::vector<std::string> ret;

	for(int i = 0; i < size; i++)
	{
		cJSON* item = cJSON_GetArrayItem(node, i);
		ret.push_back(item->string);
	}

	return ret;
}

std::vector<cJSON*> Json::getChildren(std::string key)
{
	cJSON* node = Json::findNode(key);

	int size = cJSON_GetArraySize(node);
	
	std::vector<cJSON*> ret;

	for(int i = 0; i < size; i++)
	{
		cJSON* item = cJSON_GetArrayItem(node, i);
		ret.push_back(item);
	}

	return ret;
}