#pragma once
#include "Utils.h"
#include "BoardSquare.h"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include <optional>
#include <vector>


//idea is to be able to have 2 of these for ai vs ai matches.
class AiPlayer
{
public:
    AiPlayer() = delete;
    AiPlayer(Board& boardState, const int skill);

    BoardSquare::Peices aiPeice{ BoardSquare::Peices::O };

    sf::Vector2i getMove();        // make a move based on the current difficulty level
    sf::Vector2i randomMove();
    std::optional<sf::Vector2i> immidiateWin(BoardSquare::Peices playerPeice);
    std::optional<std::vector<sf::Vector2i>> unblockedLines(BoardSquare::Peices playerPeice, const Board::BoardState& state);
    std::optional<sf::Vector2i> createFork(BoardSquare::Peices playerPeice);
    std::optional<sf::Vector2i> playCenter();

private:

    int m_skill{0};        // holds the difficulty level (1-5)
    //we will see if this works
    Board& m_aiBoardState;
};