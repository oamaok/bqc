#ifndef TILESET_H_
#define TILESET_H_

#include <vector>

#include "tiles/Tile.h"
#include "json/Json.h"

class Tileset
{
public:
	Tileset(const std::string& tilesetName);
	const Tile& getTileByIndex(int index) const;
	const Tile& getTileByName(const std::string& name) const;
	int getTileIndex(const std::string& name) const;
	std::vector<std::string> getTileNames();
private:
	std::string path;
	std::string name;
	std::string version;
	std::string author;
	std::vector<Tile> tiles;

	std::shared_ptr<Json> json;

	template <typename T> void setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue);
	template <typename T> void setTilePropertyArray(const Tile& tile, T* tileProp, int size, const std::string& key);
};

template <typename T> void Tileset::setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue)
{
	std::string fullKey = "tiles." + tile.getName() + "." + key;

	if(json->nodeExists(fullKey))
		tileProp = json->get<T>(fullKey);
	else
		tileProp = defaultValue;

}

template <typename T> void Tileset::setTilePropertyArray(const Tile& tile, T* tileProp, int size, const std::string& key)
{
	std::string fullKey =  "tiles." + tile.getName() + "." + key;

	// check if the node exists to begin with
	if(!json->nodeExists(fullKey))
		return;

	if(json->typeOf(fullKey) != Json::JsonType::TYPE_ARRAY)
		return;

	if(json->getLength(fullKey) < size)
		return;

	for(int i = 0; i < size; i++)
	{
		*tileProp = json->getArrayItem<T>(fullKey, i);
		tileProp++;
	}
}


#endif