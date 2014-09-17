#ifndef TILE_H_
#define TILE_H_

#include <string>
#include <functional>
#include <vector>

#include "player.h"
#include "side.h"

class Tile
{
public:
	Tile();
	~Tile();
	void update();
	static void addTile(Tile tile);

private:
	std::string name;
	float friction;
	bool collides;
	bool movable;
	std::function<void(Player* player, const Side side)> onHit;
	
	static std::vector<Tile> tiles;
};

#endif