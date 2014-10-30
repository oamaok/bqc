#include "json/Json.h"
#include "util/Util.h"
#include "util/Log.h"


std::unordered_map<std::string, std::shared_ptr<Json>> Json::jsonCache = std::unordered_map<std::string, std::shared_ptr<Json>>();

Json::Json(const std::string& path)
	: rootNode(nullptr)
	, error(JsonError::NO_ERROR)
{
	std::string fileContents = util::readFile(path);
	rootNode = cJSON_Parse(fileContents.c_str());

	if(!rootNode)
	{
		setError(JsonError::PARSE_ERROR);
		const char* errptr = cJSON_GetErrorPtr();
		int line = std::count(fileContents.c_str(), errptr, '\n') + 1;
		Log::error("Failed to parse JSON: %s:%d", path.c_str(), line);
	}
}

Json::JsonType Json::typeOf(std::string key)
{
	cJSON* node = findNode(key);
	switch(node->type)
	{
	case cJSON_False:
		return Json::JsonType::TYPE_BOOL;
		break;
	case cJSON_True:
		return Json::JsonType::TYPE_BOOL;
		break;
	case cJSON_NULL:
		return Json::JsonType::TYPE_NULL;
		break;
	case cJSON_Number:
		return Json::JsonType::TYPE_NUMBER;
		break;
	case cJSON_String:
		return Json::JsonType::TYPE_STRING;
		break;
	case cJSON_Array:
		return Json::JsonType::TYPE_ARRAY;
		break;
	case cJSON_Object:
		return Json::JsonType::TYPE_OBJECT;
		break;
	default:
		return Json::JsonType::TYPE_NULL;
	}
}

std::shared_ptr<Json> Json::loadJson(const std::string& path)
{
	// check the json cache for existing nodes
	auto search = jsonCache.find(path);

	if(search == jsonCache.end())
	{
		// actually load the json by calling the private constructor
		std::shared_ptr<Json> json(new Json(path));
		jsonCache[path] = json;
		return json;
	}
	
	return search->second;
}



cJSON* Json::findNode(std::string key)
{
	// load the root node for path
	cJSON* currentNode = rootNode;

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
	cJSON* node = findNode(key);
	if(node->type != cJSON_Array && node->type != cJSON_Object)
		return 0;

	return cJSON_GetArraySize(node);
}

std::vector<std::string> Json::getChildNames(std::string key)
{
	cJSON* node = findNode(key);
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
	cJSON* node = findNode(key);

	int size = cJSON_GetArraySize(node);
	
	std::vector<cJSON*> ret;

	for(int i = 0; i < size; i++)
	{
		cJSON* item = cJSON_GetArrayItem(node, i);
		ret.push_back(item);
	}

	return ret;
}

bool Json::nodeExists(std::string key)
{
	return findNode(key) != nullptr;
}