#ifndef MAP_H_
#define MAP_H_


#include <vector>
#include "tile.h"

class Map
{
public:
	Map(int width, int height);
	~Map();

	void update();
private:
	const int width;
	const int height;
	std::vector<Tile*> tiles;
};

#endif