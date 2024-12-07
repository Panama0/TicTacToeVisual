#pragma once
#include "BoardSquare.h"
#include <array>

//this is pretty much just an interface class
class Board
{
public:
    using BoardState = std::array<BoardSquare::Peices, 9>;

    BoardSquare::Peices getState(const sf::Vector2i location);
    BoardSquare::Peices getState(const int location);
    const BoardState& getState();

    void setState(const sf::Vector2i location, BoardSquare::Peices peice);
    void setState(const int location, BoardSquare::Peices peice);
    void load(const sf::Vector2i location, const char* path);

    void setPosition(const sf::Vector2i location, const sf::Vector2f position);
    const sf::Vector2f getPosition(const sf::Vector2i location);
    const sf::FloatRect& getClickbox(const sf::Vector2i location);
    const sf::FloatRect& getClickbox(const int location);

    const sf::Sprite& getSpr(const sf::Vector2i location);

    void loadDebug();

    sf::Text winnerDisplay{};

private:
    std::array<BoardSquare,9> m_board;
};