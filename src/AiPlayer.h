#pragma once
#include "Game.h"
#include "Utils.h"
#include "SFML/Graphics.hpp"
#include <random>

//idea is to be able to have 2 of these for ai vs ai matches.
class AiPlayer
{
public:
	AiPlayer() = delete;
	AiPlayer(Game::Board* const boardState);

	void makeMove();		// make a move based on the current difficulty level
	void randomMove();
	bool immidiateWin(Peice::Peices player);

private:

	int m_skill{0};		// holds the difficulty level (0-5)
	//we will see if this works
	Game::Board* const m_aiBoardState;
	Peice::Peices m_aiPeice{ Peice::Peices::O };
};