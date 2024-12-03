#include "AiPlayer.h"
#include "Board.h"
#include "BoardSquare.h"
#include "GridDim.h"
#include "Utils.h"
#include "SFML/Graphics.hpp"
#include <random>
#include <optional>
#include <vector>


AiPlayer::AiPlayer(Board& boardState)
    :m_aiBoardState{ boardState }
{
}

sf::Vector2i AiPlayer::getMove()
{
    const BoardSquare::Peices opponentPeice{ aiPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

    std::optional<sf::Vector2i> move;

    if (!(move = immidiateWin(aiPeice)))
    {
        if (!(move = immidiateWin(opponentPeice)))
        {
            if (!(move = createFork(aiPeice)))
            {
                if (!(move = createFork(opponentPeice)))
                {
                    if (!(move = playCenter()))
                    {
                        move = randomMove();
                    }
                }
            }
        }
    }

    return *move;
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

std::optional<std::vector<sf::Vector2i>> AiPlayer::unblockedLines(BoardSquare::Peices playerPeice, const Board::BoardState& state)
{
    int playerCount{};
    int opponentCount{};

    const BoardSquare::Peices opponentPeice{ playerPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

    std::vector<sf::Vector2i> move{};
    sf::Vector2i moveTemp;

    //vertical
    for (int y{}; y < 3; y++)
    {
        for (int x{}; x < 3; x++)
        {
            if (state[Utils::remap2Dto1D({x, y})] == playerPeice)
            {
                playerCount++;
            }
            else if (state[Utils::remap2Dto1D({ x, y })] == opponentPeice)
            {
                opponentCount++;
            }
            else if (state[Utils::remap2Dto1D({ x, y })] == BoardSquare::Peices::empty)
            {
                //save the blank spot
                moveTemp = { x,y };
            }
        }
        if (playerCount > 1 && opponentCount < 1)
        {        // if theres 2 O and no X present
            move.push_back(moveTemp);
        }
        playerCount = 0;
        opponentCount = 0;
    }

    //horizontal
    for (int x{}; x < 3; x++)
    {
        for (int y{}; y < 3; y++)
        {
            if (state[Utils::remap2Dto1D({ x, y })] == playerPeice)
            {
                playerCount++;
            }
            else if (state[Utils::remap2Dto1D({ x, y })] == opponentPeice)
            {
                opponentCount++;
            }
            else if (state[Utils::remap2Dto1D({ x, y })] == BoardSquare::Peices::empty)
            {
                //save the blank spot
                moveTemp = { x , y };
            }
        }
        if (playerCount > 1 && opponentCount < 1)
        {    // if theres 2 O and no X present
            move.push_back(moveTemp);
        }
        playerCount = 0;
        opponentCount = 0;
    }

    //diag right
    for (int i{}; i < 3; i++)
    {
        if (state[Utils::remap2Dto1D({ i, i })] == playerPeice)
        {
            playerCount++;
        }
        else if (state[Utils::remap2Dto1D({ i, i })] == opponentPeice)
        {
            opponentCount++;
        }
        else if (state[Utils::remap2Dto1D({ i, i })] == BoardSquare::Peices::empty)
        {
            moveTemp = { i, i };
        }
    }
    if (playerCount > 1 && opponentCount < 1)    // if theres 2 O and no X present
    {
        move.push_back(moveTemp);
    }
    playerCount = 0;
    opponentCount = 0;

    //diag left
    for (int x{}, y{ 2 }; x < 3; x++, y--) {
        if (state[Utils::remap2Dto1D({ x, y })] == playerPeice) {
            playerCount++;
        }
        else if (state[Utils::remap2Dto1D({ x, y })] == opponentPeice) {
            opponentCount++;
        }
        else if (state[Utils::remap2Dto1D({ x, y })] == BoardSquare::Peices::empty)
        {
            moveTemp = { x , y };
        }
    }
    if (playerCount > 1 && opponentCount < 1) {        // if theres 2 O and no X present
        move.push_back(moveTemp);
    }

    //no move was found
    if (move.empty())
    {
        return std::nullopt;
    }
    else
    {
        return move;
    }
}

std::optional<sf::Vector2i> AiPlayer::createFork(BoardSquare::Peices playerPeice)
{
    //make first available move
    // check for nonblocked lines of 2
    //if there's 2 then its the move

    //immieate win made into new function. new one would have to retuern multiple/all of the moves. 
    // this funct could then use the length of that array/vector to determine if theres a createFork
    //temp state would be needed here same as last time

    //imm win would hten just get the first one

    // or split each part of imm win out into seperate function. then have logic for form in the createFork function onyl

    Board::BoardState tempState = m_aiBoardState.getState();

    for (size_t i{}; i < tempState.size(); i++)
    {
        if (tempState[i] == BoardSquare::Peices::empty)
        {
            // make the first available move
            tempState[i] = playerPeice;
            if (auto lines = unblockedLines(playerPeice, tempState))
            {
                // if are more than 1 unblocked lines in this state, there is a fork.
                if ((*lines).size() > 1)
                {
                    return Utils::remap1Dto2D(i);
                }
            }
            //if nothing found reset
            tempState[i] = BoardSquare::Peices::empty;
        }
    }

    return std::nullopt;
}

std::optional<sf::Vector2i> AiPlayer::playCenter()
{
    if (m_aiBoardState.getState(4) == BoardSquare::Peices::empty)
    {
        return { { 1,1 } };
    }
    else
    {
        return std::nullopt;
    }
}
