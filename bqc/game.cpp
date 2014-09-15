#include "game.h"
#include "config.h"

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

