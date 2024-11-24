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