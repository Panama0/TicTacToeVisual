#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <string_view>

//stores resources needed by the game. no state is stored.
class tileResources
{
public:
	GameObj tiles[9];
	sf::RectangleShape highlight;

	void loadTiles(const int num, std::string_view path);
private:

};