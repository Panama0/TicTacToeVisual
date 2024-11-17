#pragma once
#include "SFML/Graphics.hpp"
#include "TileResources.h"
#include "Peice.h"
#include <array>
#include <optional>

//TODO: make this better, surely theres a better way to have these consts.
namespace GridDim
{
	const int colWidth{ 20 };
	const int spriteSize{ 256 };
	const int gridSize{ 3 };
	constexpr int gridSquares{ gridSize * gridSize };
};

//stores state only
class Game
{
public:
	using Board = std::array<std::array<Peice, 3>, 3>;
	using BoardPos = std::array<std::array<sf::Vector2f, 3>, 3>;

	Game();

	void run();
	void handleInput();
	void draw();
	void drawUI();
	void drawBoard();
	void drawPeices();
	void loadBoard();
	void placePeice(Peice::Peices peice, sf::Vector2i location);

	std::optional<const char*> Game::getPath(Peice::Peices asset);

private:
	sf::RenderWindow m_window{};
	Board m_board{};		// holds the state of the board and the peices
	Peice::Peices m_turn{ Peice::Peices::X };		// default is for X to start
	BoardPos m_boardGrid{};
	sf::Clock m_deltaClock{};

	tileResources m_resources;
};