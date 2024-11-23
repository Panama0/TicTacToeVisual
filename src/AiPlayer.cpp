#include "AiPlayer.h"
#include "Board.h"
#include "BoardSquare.h"
#include "GridDim.h"
#include "Utils.h"
#include "SFML/Graphics.hpp"
#include <random>
#include <optional>


AiPlayer::AiPlayer(Board& boardState)
    :m_aiBoardState{ boardState }
{
}

void AiPlayer::setState(Board& boardState)
{
    m_aiBoardState = boardState;
}

sf::Vector2i AiPlayer::getMove()
{
    const BoardSquare::Peices opponentPeice{ aiPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

    std::optional<sf::Vector2i> move;

    //TODO: make the below more scalable, endless ifs cant be the best way to go
    if (!(move = immidiateWin(aiPeice)))
    {
        if (!(move = immidiateWin(opponentPeice)))
        {
            return randomMove();
        }
        else
        {
            return *move;
        }
    }
    else
    {
        return *move;
    }
}

sf::Vector2i AiPlayer::randomMove()
{
    sf::Vector2i move{};

    do
    {
        move = Utils::remap1Dto2D(Utils::getRandomNumber(0, GridDim::gridSquares - 1));
    } while (m_aiBoardState.getState(move) != BoardSquare::Peices::empty);
    

    return move;
}

//search for 2 in a row and then return the move if it can be made
std::optional<sf::Vector2i>  AiPlayer::immidiateWin(BoardSquare::Peices playerPeice)
{
    int playerCount{};
    int opponentCount{};

    const BoardSquare::Peices opponentPeice{ playerPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

    std::optional<sf::Vector2i> move{ {0,0} };

    //vertical
    for (int y{}; y < 3; y++)
    {
        for (int x{}; x < 3; x++)
        {
            if (m_aiBoardState.getState({x,y}) == playerPeice)
            {
                playerCount++;
            }
            else if (m_aiBoardState.getState({x,y}) == opponentPeice)
            {
                opponentCount++;
            }
            else if (m_aiBoardState.getState({x,y}) == BoardSquare::Peices::empty)
            {
                //save the blank spot
                move = { x , y };
            }
        }
        if (playerCount > 1 && opponentCount < 1)
        {        // if theres 2 O and no X present
            return move;
        }
        playerCount = 0;
        opponentCount = 0;
    }

    //horizontal
    for (int x{}; x < 3; x++)
    {
        for (int y{}; y < 3; y++)
        {
            if (m_aiBoardState.getState({x,y}) == playerPeice)
            {
                playerCount++;
            }
            else if (m_aiBoardState.getState({x,y}) == opponentPeice)
            {
                opponentCount++;
            }
            else if (m_aiBoardState.getState({x,y}) == BoardSquare::Peices::empty)
            {
                //save the blank spot
                move = { x , y };
            }
        }
        if (playerCount > 1 && opponentCount < 1)
        {    // if theres 2 O and no X present
            return move;
        }
        playerCount = 0;
        opponentCount = 0;
    }

    //diag right
    for (int i{}; i < 3; i++)
    {
        if (m_aiBoardState.getState({i,i}) == playerPeice)
        {
            playerCount++;
        } 
        else if (m_aiBoardState.getState({i,i}) == opponentPeice)
        {
            opponentCount++;
        }
        else if (m_aiBoardState.getState({i,i}) == BoardSquare::Peices::empty)
        {
            move = { i, i };
        }
    }
    if (playerCount > 1 && opponentCount < 1)    // if theres 2 O and no X present
    {
        return move;
    }
    playerCount = 0;
    opponentCount = 0;

    //diag left
    for (int x{}, y{ 2 }; x < 3; x++, y--) {
        if (m_aiBoardState.getState({x,y}) == playerPeice) {
            playerCount++;
        }
        else if (m_aiBoardState.getState({x,y}) == opponentPeice) {
            opponentCount++;
        }
        else if (m_aiBoardState.getState({x,y}) == BoardSquare::Peices::empty)
        {
            move = { x , y };
        }
    }
    if (playerCount > 1 && opponentCount < 1) {        // if theres 2 O and no X present
        return move;
    }

    //no move was found
    return std::nullopt;
}
