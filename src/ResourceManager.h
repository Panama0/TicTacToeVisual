#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <string_view>


class GameObj
{
public:
	sf::Sprite sprite;

	void loadTexture(std::string_view path);
private:
	sf::Texture m_texture;
};


//stores resources needed by the game. no state is stored.
class ResMan
{
public:
	GameObj tiles[9];
	std::vector<GameObj> peices;

	void loadTiles(const int num, std::string_view path);
private:

};