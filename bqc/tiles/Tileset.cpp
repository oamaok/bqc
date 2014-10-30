#include "tiles/Tileset.h"
#include "json/Json.h"
#include "util/Log.h"

Tileset::Tileset(const std::string& name)
	: path("tilesets/" + name + ".json")
	, json(Json::loadJson(path))
{
	if(!json)
	{
		Log::error("Couldn't load tileset '%s'.", name.c_str());
		return;
	}

	this->name = json->get<std::string>("name");
	this->author = json->get<std::string>("version");
	// get tile names
	std::vector<std::string> tileNames = json->getChildNames("tiles");

	for(auto& tileName : tileNames)
	{
		Tile tile(tileName);

		std::vector<std::string> childNames = json->getChildNames("tiles." + tileName);

		// fetch properties for tiles or fill in the defaults if not set
		setTileProperty<bool>(tile, tile.collides, "collides", false);
		setTileProperty<bool>(tile, tile.movable, "movable", false);
		setTileProperty<int>(tile, tile.limit, "limit", 0);
		setTileProperty<int>(tile, tile.require, "require", 0);
		setTilePropertyArray<int>(tile, tile.texture, 2, "texture", {0,0});

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
	return -1;
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

bool Tileset::isArrayNodeValid(const std::string& key, int size)
{
	return (!json->nodeExists(key) // check if the node exists to begin with
		|| json->typeOf(key) != Json::JsonType::TYPE_ARRAY // check for right type
		|| json->getLength(key) < size // check if the array is the right size or larger
		);
}