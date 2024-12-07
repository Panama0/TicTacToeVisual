#include "AiPlayer.h"
#include "Board.h"
#include "BoardSquare.h"
#include "GridDim.h"
#include "Utils.h"
#include "SFML/Graphics.hpp"
#include <optional>
#include <vector>


AiPlayer::AiPlayer(Board& boardState, const int& skill)
    :m_aiBoardState{ boardState }
    ,m_skill{skill}
{
}

sf::Vector2i AiPlayer::getMove()
{
    const BoardSquare::Peices opponentPeice{ aiPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

    std::optional<sf::Vector2i> move;
    //skill check

    if (m_skill <= Utils::getRandomNumber(1, 4))
    {
        move = randomMove();
        return *move;
    }


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
    if (auto move = unblockedLines(playerPeice, m_aiBoardState.getState()))
    {
        return (*move).front();
    }
    else
    {
        return std::nullopt;
    }
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
