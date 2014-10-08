#ifndef JSON_H_
#define JSON_H_

#include <string>
#include <unordered_map>
#include <memory>
#include "json/cJSON.h"
#include "util/util.h"

class Json
{
public:
	enum JsonType {
		TYPE_BOOL,
		TYPE_NULL,
		TYPE_NUMBER,
		TYPE_STRING,
		TYPE_ARRAY,
		TYPE_OBJECT
	};

	static JsonType typeOf(const std::string path, const std::string key);
	static cJSON* loadJson(const std::string path);
	static cJSON* findNode(const std::string path, const std::string key);
	template <typename T> static T get(const std::string path, const std::string key);
	static std::vector<std::string> getChildren(const std::string path, const std::string key);
	static int getLength(const std::string path, const std::string key);

private:
	static std::unordered_map<std::string, std::shared_ptr<cJSON>> rootNodes;
};


template <typename T> T Json::get(std::string key)
{
	cJSON* node = Json::findNode(key);
	if(node == nullptr)
		return T();
	return util::jsonCast<T>(node);
}



#endif