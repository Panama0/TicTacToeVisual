#pragma once
#include "SFML/Graphics.hpp"
#include "TileResources.h"
#include "BoardSquare.h"
#include "BoardState.h"
#include "GridDim.h"
#include "AiPlayer.h"
#include <array>
#include <optional>

class Game
{
public:
	Game();

	void run();
	void handleInput();
	void draw();
	void drawUI();
	void drawBoard();
	void drawPeices();
	void loadBoard();
	void placePeice(BoardSquare::Peices peice, sf::Vector2i location);
	void makeAiMove();

	void reset();

	std::optional<const char*> Game::getPath(BoardSquare::Peices asset);
private:
	sf::RenderWindow m_window{};
	BoardState m_board{};		// holds the state of the board and the peices
	BoardSquare::Peices m_turn{ BoardSquare::Peices::X };		// default is for X to start
	sf::Clock m_deltaClock{};

	AiPlayer m_AiPlayer;

	tileResources m_resources;
};