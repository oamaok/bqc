#ifndef TILE_H_
#define TILE_H_

#include <string>
#include <functional>
#include <vector>

#include "player/player.h"

class Tile
{
public:
	Tile();
	~Tile();
	void update();
	void render();

	void onHit();
	
private:
	std::string name;
	bool collides;
	bool movable;
	int texture[2];
};

#endif