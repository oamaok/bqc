#include "game.h"

Game::Game()
	: map(Config::get<int>("map.width"), Config::get<int>("map.height"))
{

}

void Game::start()
{

}

void Game::stop()
{

}

void Game::main()
{

}

void Game::update()
{
	map.update();
	for(int i = 0; i < 2; i++)
	{
		players[i].update();
	}
}

void Game::render()
{
	map.render();

}