#pragma once
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp" //for vector

namespace Utils
{
    static sf::Vector2i remap1Dto2D(const int index)
    {
        const int remap[9][2] = { {0,0}, {1,0}, {2,0},
                                  {0,1}, {1,1}, {2,1},
                                  {0,2}, {1,2}, {2,2} };
        if (index < 9)
        {
            return sf::Vector2i(remap[index][0], remap[index][1]);
        }
        else
        {
            std::cerr << "Could not remap, Outside bounds!";
            return { 0,0 };
        }
    }

    static int remap2Dto1D(const sf::Vector2i index)
    {
        const int remap[3][3]{{{0}, {1}, {2}}
                             ,{{3}, {4}, {5}}
                             ,{{6}, {7}, {8}}};

        return remap[index.y][index.x];
    }

    static int getRandomNumber(const int min, const int max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> randMove(min, max);

        return randMove(gen);
    }
}