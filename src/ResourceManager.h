#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <vector>
#include <string>
#include <string_view>

//stores resources needed by the game. no state is stored.
class ResMan
{
public:
	GameObj tiles[9];
	sf::RectangleShape highlight;
	std::vector<GameObj> peices;

	void loadTiles(const int num, std::string_view path);
private:

};