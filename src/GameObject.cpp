#include "GameObject.h"
#include "Game.h"
#include <string_view>
#include <iostream>


void GameObj::loadTexture(std::string_view path)
{
    if (!m_texture.loadFromFile(path.data()))
    {
        std::cerr << "Could not load file!";
    }
    sprite.setTexture(m_texture);
}

sf::Rect<float>& GameObj::getClickbox()
{

    sf::FloatRect bounds{sprite.getGlobalBounds() };
    bounds.height -= GridDim::colWidth * 2;
    bounds.width -= GridDim::colWidth * 2;
    bounds.left += GridDim::colWidth;
    bounds.top += GridDim::colWidth;
    return bounds;
}
