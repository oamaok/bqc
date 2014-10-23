#include "tiles/Tile.h"

void Tile::update()
{

}

void Tile::render()
{

}

Tile::Tile(const std::string& name)
	: name(name)
{

}

Tile::~Tile()
{

}

std::string Tile::getName()
{
	return name;
}