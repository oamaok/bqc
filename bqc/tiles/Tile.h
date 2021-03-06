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

	bool collides;
	bool movable;
	int texture[2];
	int limit;
	int require;
	const std::string getName() const;
	
private:
	std::string name;
};

#endif