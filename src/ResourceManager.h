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
	ResMan();

	GameObj tiles[9];
	sf::RectangleShape highlight;
	//TODO: this is not de way. perhaps the gameboard/game obj could store a pointer to the specific sprite used by itself therefore
	//it would keep track of its own resources
	std::vector<GameObj> PeicesX;
	std::vector<GameObj> PeicesO;

	void loadTiles(const int num, std::string_view path);
	//TODO use same type of string in all, mixing stringviews and cstr is a nightmare
	void addSpr(const char* path);
private:

};