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

	template <typename T> void setTileProperty(const std::string& tileName, T& tileProp, const std::string& key, const T& defaultValue);
};

template <typename T> void Tileset::setTileProperty(const std::string& tileName, T& tileProp, const std::string& key, const T& defaultValue)
{
	if(Json::findNode(path, "tiles." + tileName + "." + key))
	{
		tileProp = Json::get<T>(path, "tiles." + tileName + "." + key);
	}
	else
	{
		tileProp = defaultValue;
	}
}


#endif