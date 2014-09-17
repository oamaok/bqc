#ifndef MAP_H_
#define MAP_H_


#include <vector>
#include "tiles/Tile.h"

class Map
{
public:
	Map(int width, int height);
	~Map();

	void update();
	void render();
private:
	const int width;
	const int height;
	std::vector<Tile*> tiles;
};

#endif