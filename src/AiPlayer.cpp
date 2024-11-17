#include "AiPlayer.h"
#include "game.h"
#include "SFML/Graphics.hpp"


AiPlayer::AiPlayer(Game::Board* const boardState)
	:m_aiBoardState{ boardState }
{
}

void AiPlayer::makeMove()
{
	const Peice::Peices opponentPeice{ m_aiPeice == Peice::Peices::X ? Peice::Peices::O : Peice::Peices::X };

	//TODO: make the below more scalable, endless ifs cant be the best way to go
	if (!immidiateWin(m_aiPeice))
	{
		if (!immidiateWin(opponentPeice))
		{
			randomMove();
		}
	}

}

void AiPlayer::randomMove()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randMove(0, GridDim::gridSquares - 1);

	int move{ randMove(gen) };

	sf::Vector2i temp = remap1Dto2D(move);
	(*m_aiBoardState)[temp.x][temp.y].corePeice = m_aiPeice;

}

//search for 2 in a row and then make the move in that spot.
bool AiPlayer::immidiateWin(Peice::Peices playerPeice)
{
	int aiCount{};
	int opponentCount{};

	const Peice::Peices opponentPeice{ playerPeice == Peice::Peices::X ? Peice::Peices::O : Peice::Peices::X };

	sf::Vector2i move;

	//Game::Peice test = (*m_aiBoardState)[0][0];

	//vertical
	for (int y{}; y < 3; y++)
	{
		for (int x{}; x < 3; x++)
		{
			if ((*m_aiBoardState)[x][y].corePeice == playerPeice)
			{
				aiCount++;
			}
			else if ((*m_aiBoardState)[x][y].corePeice == opponentPeice)
			{
				opponentCount++;
			}
			else if ((*m_aiBoardState)[x][y].corePeice == Peice::Peices::empty)
			{
				//save the blank spot
				move = { x , y };
			}
		}
		if (aiCount > 1 && opponentCount < 1)
		{		// if theres 2 O and no X present
			(*m_aiBoardState)[move.x][move.y].corePeice = m_aiPeice;
			return true;
		}
		aiCount = 0;
		opponentCount = 0;
	}

	//horizontal
	for (int x{}; x < 3; x++)
	{
		for (int y{}; y < 3; y++)
		{
			if ((*m_aiBoardState)[x][y].corePeice == playerPeice)
			{
				aiCount++;
			}
			else if ((*m_aiBoardState)[x][y].corePeice == opponentPeice)
			{
				opponentCount++;
			}
			else if ((*m_aiBoardState)[x][y].corePeice == Peice::Peices::empty)
			{
				//save the blank spot
				move = { x , y };
			}
		}
		if (aiCount > 1 && opponentCount < 1)
		{	// if theres 2 O and no X present
			(*m_aiBoardState)[move.x][move.y].corePeice = m_aiPeice;
			return true;
		}
		aiCount = 0;
		opponentCount = 0;
	}

	//diag right
	for (int i{}; i < 3; i++)
	{
		if ((*m_aiBoardState)[i][i].corePeice == playerPeice)
		{
			aiCount++;
		} 
		else if ((*m_aiBoardState)[i][i].corePeice == opponentPeice)
		{
			opponentCount++;
		}
		else if ((*m_aiBoardState)[i][i].corePeice == Peice::Peices::empty)
		{
			move = { i, i };
		}
	}
	if (aiCount > 1 && opponentCount < 1)	// if theres 2 O and no X present
	{
		(*m_aiBoardState)[move.x][move.y].corePeice = m_aiPeice;
		return true;
	}
	aiCount = 0;
	opponentCount = 0;

	//diag left
	for (int x{}, y{ 2 }; x < 3; x++, y--) {
		if ((*m_aiBoardState)[x][y].corePeice == playerPeice) {
			aiCount++;
		}
		else if ((*m_aiBoardState)[x][y].corePeice == opponentPeice) {
			opponentCount++;
		}
		else {
			move = { x , y };
		}
	}
	if (aiCount > 1 && opponentCount < 1) {		// if theres 2 O and no X present
		(*m_aiBoardState)[move.x][move.y].corePeice = m_aiPeice;
		return true;
	}

	//no move was found
	return false;
}
