#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include <array>
#include <optional>


//stores state only
class Game
{
public:
	enum Peice;
	using Board = std::array<std::array<Peice, 3>, 3>;
	using BoardPos = std::array<std::array<sf::Vector2f, 3>, 3>;

	Game();

	void run();
	void handleInput();
	void draw();
	void drawUI();
	void drawBoard();
	void loadBoard();

	std::optional<const char*> Game::getPath(Game::Peice asset);

private:
	sf::RenderWindow m_window{};
	Board m_boardState{};
	BoardPos m_boardGrid{};
	sf::Clock m_deltaClock{};

	ResMan m_resources;
};