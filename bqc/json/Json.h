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

	Json(const std::string& path);
	~Json();

	JsonType typeOf(std::string key);
	static Json& loadJson(const std::string& path);
	cJSON* findNode(std::string key);
	template <typename T> const T get(std::string key);
	std::vector<std::string> getChildNames(std::string key);
	std::vector<cJSON*> getChildren(std::string key);
	int getLength(std::string key);
	std::string getPath();
private:
	std::string path;
	std::shared_ptr<cJSON> rootNode;

	static std::unordered_map<std::string, Json> jsonCache;
};


template <typename T> const T Json::get(std::string key)
{
	cJSON* node = Json::findNode(key);
	if(node == nullptr)
		return T();
	return util::jsonCast<T>(node);
}

#endif