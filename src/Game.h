#pragma once
#include "SFML/Graphics.hpp"
#include "TileResources.h"
#include "BoardSquare.h"
#include "Board.h"
#include "GridDim.h"
#include "AiPlayer.h"
#include <array>
#include <optional>

class Game
{
public:
    Game();

    void run();
    void reset();

    std::optional<const char*> getPath(BoardSquare::Peices asset);
private:
    void handleInput();
    void draw();
    void drawUI();
    void drawBoard();
    void drawPeices();
    void loadBoard();
    void placePeice(BoardSquare::Peices peice, sf::Vector2i location);
    void makeAiMove();
    std::optional<BoardSquare::Peices> checkVictory();


    sf::RenderWindow m_window{};
    Board m_board{};        // holds the state of the board and the peices
    BoardSquare::Peices m_turn{ BoardSquare::Peices::X };        // default is for X to start
    int m_turnCount{};
    BoardSquare::Peices m_playerPeice{ BoardSquare::Peices::X };
    
    std::optional<BoardSquare::Peices> m_winner{std::nullopt};       //null is no winner

    sf::Clock m_deltaClock{};

    AiPlayer m_AiPlayer;

    tileResources m_resources;
};