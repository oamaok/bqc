#ifndef TILESET_H_
#define TILESET_H_

#include <vector>

#include "tiles/Tile.h"

class Tileset
{
public:
	Tileset(const std::string& tilesetName);
	const Tile& getTileByIndex(int index) const;
	const Tile& getTileByName(const std::string& name) const;
	int getTileIndex(const std::string& name) const;
private:
	std::vector<Tile> tiles;
};


#endif