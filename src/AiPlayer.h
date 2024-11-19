#pragma once
#include "Utils.h"
#include "BoardSquare.h"
#include "BoardState.h"
#include "SFML/Graphics.hpp"
#include <optional>


//idea is to be able to have 2 of these for ai vs ai matches.
class AiPlayer
{
public:
	AiPlayer() = delete;
	AiPlayer(BoardState* const boardState);

	BoardSquare::Peices aiPeice{ BoardSquare::Peices::O };

	void setState(BoardState* const boardState);

	sf::Vector2i getMove();		// make a move based on the current difficulty level
	sf::Vector2i randomMove();
	std::optional<sf::Vector2i> immidiateWin(BoardSquare::Peices player);

private:

	int m_skill{0};		// holds the difficulty level (0-5)
	//we will see if this works
	BoardState* m_aiBoardState;
};