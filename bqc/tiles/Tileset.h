#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <initializer_list>

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

	bool isArrayNodeValid(const std::string& key, int size);

	template <typename T> void setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue);
	template <typename T> void setTilePropertyArray(const Tile& tile, T* tileProp, int size, const std::string& key, const std::initializer_list<T>& defaultValue);
};

template <typename T> void Tileset::setTileProperty(const Tile& tile, T& tileProp, const std::string& key, const T& defaultValue)
{
	std::string fullKey = "tiles." + tile.getName() + "." + key;

	if(json->nodeExists(fullKey))
		tileProp = json->get<T>(fullKey);
	else
		tileProp = defaultValue;

}

template <typename T> void Tileset::setTilePropertyArray(const Tile& tile, T* tileProp, int size, const std::string& key, const std::initializer_list<T>& defaultValue)
{
	std::string fullKey =  "tiles." + tile.getName() + "." + key;

	if (isArrayNodeValid(fullKey, size))
	{
		if (defaultValue.size() < size) // default value too small, exit
			return;

		for (int i = 0; i < size; i++)
		{
			*tileProp = defaultValue[i];
			tileProp++;
		}
		return;
	}

	for(int i = 0; i < size; i++)
	{
		*tileProp = json->getArrayItem<T>(fullKey, i);
		tileProp++;
	}
}


#endif