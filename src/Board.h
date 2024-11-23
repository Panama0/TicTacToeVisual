#pragma once
#include "BoardSquare.h"
#include <array>

//this is pretty much just an interface class
class Board
{
public:
    // this will save us putting .board.state everywhere
    //can also add another member function to get the 
    BoardSquare::Peices getState(const sf::Vector2i location);
    BoardSquare::Peices getState(const int location);

    void setState(const sf::Vector2i location, BoardSquare::Peices peice);
    void setState(const int location, BoardSquare::Peices peice);
    void load(const sf::Vector2i location, const char* path);

    void setPosition(const sf::Vector2i location, const sf::Vector2f position);
    const sf::Vector2f getPosition(const sf::Vector2i location);

    const sf::Sprite& getSpr(const sf::Vector2i location);
private:
    std::array<BoardSquare,9> m_board;
};