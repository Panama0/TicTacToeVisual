#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include <array>

class Game
{
public:
	enum Peice
	{
		empty,
		X,
		O,
	};
	using Board = std::array<std::array<Peice, 3>, 3>;
	using BoardPos = std::array<std::array<sf::Vector2f, 3>, 3>;

	Game();

	void run();
	void handleInput();
	void draw();
	void drawUI();
	void drawBoard();
	void loadBoard();

private:
	sf::RenderWindow m_window{};
	Board m_boardState{};
	BoardPos m_boardGrid{};
	sf::Clock m_deltaClock{};

	GameObj m_tiles[9];
};