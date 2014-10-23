#ifndef TILESET_H_
#define TILESET_H_

#include <vector>

#include "tiles/Tile.h"

class Tileset
{
public:
	Tile getTile(int index);
	Tile getTile(std::string name);
	void loadTileset(std::string path);
private:
	std::vector<Tile> tiles;
};


#endif