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

	template <typename T> void setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue);
	template <typename T> void setTilePropertyArray(const Tile& tile, T* tileProp, size_t size, const std::string& key);
};

template <typename T> void Tileset::setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue)
{
	std::string fullKey = "tiles." + tile.name + "." + key;
	if(Json::findNode(path, fullKey))
	{
		tileProp = Json::get<T>(path, fullKey);
	}
	else
	{
		tileProp = defaultValue;
	}

}

template <typename T> void Tileset::setTilePropertyArray(const Tile& tile, T* tileProp, size_t size, const std::string& key)
{
	std::string fullKey =  "tiles." + tile.name + "." + key;
	if(!Json::findNode(path, fullKey))
		return;

	if(Json::getLength(path, fullKey) >= 2)
	{
		
	}
}


#endif