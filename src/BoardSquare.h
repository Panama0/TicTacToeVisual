#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"

class BoardSquare
{
public:
    enum class Peices
    {
        empty,
        X,
        O,
        tile,
    };

    Peices squareState{ Peices::empty };
    sf::Vector2f position{};        //in world space of the square
    
    void load(const char* path);

    sf::Sprite& getSpr() { return m_obj.sprite; };
private:
    GameObj m_obj;
};

