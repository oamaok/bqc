#ifndef TILE_H_
#define TILE_H_

#include <string>
#include <functional>
#include <vector>

#include "player/player.h"

class Tile
{
public:
	Tile(const std::string& name);
	~Tile();
	void update();
	void render();

	std::string getName();
	
private:
	std::string name;
	bool collides;
	bool movable;
	int texture[2];
};

#endif