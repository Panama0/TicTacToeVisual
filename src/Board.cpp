#include "Board.h"
#include "Utils.h"
#include "GridDim.h"

BoardSquare::Peices Board::getState(const sf::Vector2i location)
{
    return m_board[Utils::remap2Dto1D(location)].squareState;
}

BoardSquare::Peices Board::getState(const int location)
{
    return m_board[location].squareState;
}

const Board::BoardState& Board::getState()
{
    Board::BoardState state{};

    for (size_t i{}; i < state.size(); i++)
    {
        state[i] = getState(i);
    }
    return state;
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

const sf::FloatRect& Board::getClickbox(const sf::Vector2i location)
{
    sf::Vector2f origin{ m_board[Utils::remap2Dto1D(location)].position };
    sf::FloatRect bounds(origin.x + GridDim::colWidth, origin.y + GridDim::colWidth, 
                        GridDim::spriteSize - GridDim::colWidth * 2, GridDim::spriteSize - GridDim::colWidth * 2);

    return bounds;
}

const sf::FloatRect& Board::getClickbox(const int location)
{
    return getClickbox(Utils::remap1Dto2D(location));
}



const sf::Sprite& Board::getSpr(const sf::Vector2i location)
{
    return m_board[Utils::remap2Dto1D(location)].getSprite();
}

void Board::loadDebug()
{
    m_board[0].squareState = BoardSquare::Peices::empty;
    m_board[1].squareState = BoardSquare::Peices::empty;
    m_board[2].squareState = BoardSquare::Peices::empty;
    m_board[3].squareState = BoardSquare::Peices::empty;
    m_board[4].squareState = BoardSquare::Peices::empty;
    m_board[5].squareState = BoardSquare::Peices::empty;
    m_board[6].squareState = BoardSquare::Peices::empty;
    m_board[7].squareState = BoardSquare::Peices::empty;
    m_board[8].squareState = BoardSquare::Peices::empty;



    m_board[0].squareState = BoardSquare::Peices::X;
    m_board[4].squareState = BoardSquare::Peices::X;
    //m_board[3].squareState = BoardSquare::Peices::empty;

    //m_board[2].squareState = BoardSquare::Peices::O;
    //m_board[4].squareState = BoardSquare::Peices::O;
    //m_board[6].squareState = BoardSquare::Peices::O;
}
