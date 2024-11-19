#include "AiPlayer.h"
#include "BoardState.h"
#include "BoardSquare.h"
#include "GridDim.h"
#include "SFML/Graphics.hpp"
#include <random>
#include <optional>


AiPlayer::AiPlayer(BoardState* const boardState)
	:m_aiBoardState{ boardState }
{
}

void AiPlayer::setState(BoardState* const boardState)
{
	m_aiBoardState = boardState;
}

sf::Vector2i AiPlayer::getMove()
{
	const BoardSquare::Peices opponentPeice{ aiPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

	//temp
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randMove(0, GridDim::gridSquares - 1);

	sf::Vector2i move2d{};

	do
	{
		move2d = remap1Dto2D(randMove(gen));
	} while ((*m_aiBoardState).board[move2d.x][move2d.y].squareState != BoardSquare::Peices::empty);
	

	return move2d;
}

//search for 2 in a row and then return the move if it can be made
std::optional<sf::Vector2i>  AiPlayer::immidiateWin(BoardSquare::Peices playerPeice)
{
	int aiCount{};
	int opponentCount{};

	const BoardSquare::Peices opponentPeice{ playerPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };

	sf::Vector2i move;

	//vertical
	for (int y{}; y < 3; y++)
	{
		for (int x{}; x < 3; x++)
		{
			if ((*m_aiBoardState).board[x][y].squareState == playerPeice)
			{
				aiCount++;
			}
			else if ((*m_aiBoardState).board[x][y].squareState == opponentPeice)
			{
				opponentCount++;
			}
			else if ((*m_aiBoardState).board[x][y].squareState == BoardSquare::Peices::empty)
			{
				//save the blank spot
				move = { x , y };
			}
		}
		if (aiCount > 1 && opponentCount < 1)
		{		// if theres 2 O and no X present
			return move;
		}
		aiCount = 0;
		opponentCount = 0;
	}

	//horizontal
	for (int x{}; x < 3; x++)
	{
		for (int y{}; y < 3; y++)
		{
			if ((*m_aiBoardState).board[x][y].squareState == playerPeice)
			{
				aiCount++;
			}
			else if ((*m_aiBoardState).board[x][y].squareState == opponentPeice)
			{
				opponentCount++;
			}
			else if ((*m_aiBoardState).board[x][y].squareState == BoardSquare::Peices::empty)
			{
				//save the blank spot
				move = { x , y };
			}
		}
		if (aiCount > 1 && opponentCount < 1)
		{	// if theres 2 O and no X present
			return move;
		}
		aiCount = 0;
		opponentCount = 0;
	}

	//diag right
	for (int i{}; i < 3; i++)
	{
		if ((*m_aiBoardState).board[i][i].squareState == playerPeice)
		{
			aiCount++;
		} 
		else if ((*m_aiBoardState).board[i][i].squareState == opponentPeice)
		{
			opponentCount++;
		}
		else if ((*m_aiBoardState).board[i][i].squareState == BoardSquare::Peices::empty)
		{
			move = { i, i };
		}
	}
	if (aiCount > 1 && opponentCount < 1)	// if theres 2 O and no X present
	{
		return move;
	}
	aiCount = 0;
	opponentCount = 0;

	//diag left
	for (int x{}, y{ 2 }; x < 3; x++, y--) {
		if ((*m_aiBoardState).board[x][y].squareState == playerPeice) {
			aiCount++;
		}
		else if ((*m_aiBoardState).board[x][y].squareState == opponentPeice) {
			opponentCount++;
		}
		else {
			move = { x , y };
		}
	}
	if (aiCount > 1 && opponentCount < 1) {		// if theres 2 O and no X present
		return move;
	}

	//no move was found
	return std::nullopt;
}
