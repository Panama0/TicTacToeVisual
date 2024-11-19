#pragma once
#include "BoardSquare.h"
#include <array>

struct BoardState
{
public:
    using Board = std::array<std::array<BoardSquare, 3>, 3>;

    Board board;
};