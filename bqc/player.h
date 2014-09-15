#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm\glm.hpp>

class Player
{
public:
	void update();
	void render();
private:
	glm::vec2 position;
	glm::vec2 velocity;

};

#endif