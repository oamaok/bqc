#include "tiles/Tileset.h"
#include "json/Json.h"
#include "util/Log.h"

Tileset::Tileset(const std::string& name)
{
	std::string path = "tilesets/" + name + ".json";

	if(!Json::loadJson(path))
	{
		Log::error("Couldn't load tileset '%s'.", name.c_str());
		return;
	}

	// get root node child names
	std::vector<std::string> childNames = Json::getChildNames(path, "");

	for(auto& childName : childNames)
	{
		Tile tile(childName);
		tiles.push_back(tile);
	}
}

const Tile& Tileset::getTileByIndex(int index) const
{
	return tiles.at(index);
}

const Tile& Tileset::getTileByName(const std::string& name) const
{
	for(auto& tile : tiles)
	{
		if(tile.getName() == name)
			return tile;
	}
}

int Tileset::getTileIndex(const std::string& name) const
{
	for(std::vector<Tile>::size_type i = 0; i != tiles.size(); i++)
	{	
		if(tiles[i].getName() == name)
			return (int)i;
	}
}