#ifndef GAME_H_
#define GAME_H_


#include "util/config.h"
#include "entities/map.h"
#include "player/player.h"


class Game
{
public:
	Game();
	~Game();
	void start();
	void stop();
private:
	Map map;
	Player players[2];

	bool running;
	int frame;
	
	int init();
	void main();
	void update();
	void render();
};

#endif