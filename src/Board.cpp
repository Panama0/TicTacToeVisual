#include "Board.h"
#include "Utils.h"

BoardSquare::Peices Board::getState(const sf::Vector2i location)
{
    return m_board[Utils::remap2Dto1D(location)].squareState;
}

BoardSquare::Peices Board::getState(const int location)
{
    return m_board[location].squareState;
}

void Board::setState(const sf::Vector2i location, BoardSquare::Peices peice)
{
    m_board[Utils::remap2Dto1D(location)].squareState = peice;
    m_board[Utils::remap2Dto1D(location)].getSprite().setPosition(m_board[Utils::remap2Dto1D(location)].position);
}

void Board::setState(const int location, BoardSquare::Peices peice)
{
    m_board[location].squareState = peice;
    m_board[location].getSprite().setPosition(m_board[location].position);
}

void Board::load(const sf::Vector2i location, const char* path)
{
    m_board[Utils::remap2Dto1D(location)].load(path);
}

void Board::setPosition(const sf::Vector2i location, const sf::Vector2f position)
{
    m_board[Utils::remap2Dto1D(location)].position = position;
}

const sf::Vector2f Board::getPosition(const sf::Vector2i location)
{
    return m_board[Utils::remap2Dto1D(location)].position;
}

const sf::Sprite& Board::getSpr(const sf::Vector2i location)
{
    return m_board[Utils::remap2Dto1D(location)].getSprite();
}
