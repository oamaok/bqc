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

	enum JsonError {
		NO_ERROR = -1,
		PARSE_ERROR,
	};

	static std::shared_ptr<Json> loadJson(const std::string& path);
	std::string getPath();

	cJSON* findNode(std::string key);
	JsonType typeOf(std::string key);
	std::vector<std::string> getChildNames(std::string key);
	std::vector<cJSON*> getChildren(std::string key);
	int getLength(std::string key);
	template <typename T> const T get(std::string key);
	template <typename T> const T getArrayItem(std::string key, int index);
	bool nodeExists(std::string key);
	JsonError getError() { return error; };
	operator bool() const { return error == JsonError::NO_ERROR; };
private:
	Json(const std::string& path);
	void setError(JsonError err) { error = err; };
	std::string path;
	cJSON* rootNode;
	static std::unordered_map<std::string, std::shared_ptr<Json>> jsonCache;
	JsonError error;
};


template <typename T> const T Json::get(std::string key)
{
	cJSON* node = findNode(key);
	if(node == nullptr)
		return T();
	return util::jsonCast<T>(node);
}

template <typename T> const T Json::getArrayItem(std::string key, int index)
{
	cJSON* node = findNode(key);
	if(node == nullptr)
		return T();
	return util::jsonCast<T>(cJSON_GetArrayItem(node, index));
}

#endif