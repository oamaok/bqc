#include "tiles/Tileset.h"
#include "json/Json.h"
#include "util/Log.h"

Tileset::Tileset(const std::string& name)
	: path("tilesets/" + name + ".json")
{
	if(!Json::loadJson(path))
	{
		Log::error("Couldn't load tileset '%s'.", name.c_str());
		return;
	}
	this->name = Json::get<std::string>(path, "name");
	this->author = Json::get<std::string>(path, "version");
	// get tile names
	std::vector<std::string> tileNames = Json::getChildNames(path, "tiles");

	for(auto& tileName : tileNames)
	{
		Tile tile(tileName);

		std::vector<std::string> childNames = Json::getChildNames(path, "tiles." + tileName);

		setTileProperty<bool>(tileName, tile.collides, "collides", false);
		setTileProperty<bool>(tileName, tile.movable, "movable", false);
		setTileProperty<int>(tileName, tile.limit, "limit", 0);
		setTileProperty<int>(tileName, tile.require, "require", 0);

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

std::vector<std::string> Tileset::getTileNames()
{
	std::vector<std::string> names;
	for(const auto& tile : tiles)
	{
		names.push_back(tile.getName());
	}
	return names;
}