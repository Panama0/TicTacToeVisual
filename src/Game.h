#pragma once
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

	Game();
	void run();
	void handleInput();
	void draw();
	void drawUI();

private:
	sf::RenderWindow m_window{};
	Board m_board{};
	sf::Clock m_deltaClock{};
};