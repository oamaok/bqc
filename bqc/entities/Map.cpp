#include "map.h"

Map::Map(int width, int height)
	:width(width), height(height), tiles(width * height, nullptr)
{
}

Map::~Map()
{
	for(Tile* tile : tiles)
		delete tile;
}

void Map::update()
{
	for(Tile* tile : tiles)
	{
		if(tile == nullptr)
			continue;

		tile->update();
	}
}

void Map::render()
{
	for(Tile* tile : tiles)
	{
		if(tile == nullptr)
			continue;

		tile->render();
	}

}