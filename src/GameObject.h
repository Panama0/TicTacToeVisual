#pragma once
#include "SFML/Graphics.hpp"
#include <string_view>

class GameObj
{
public:
    sf::Sprite sprite;

    void loadTexture(std::string_view path);

    //sf::Rect<float>& getClickbox();
private:
    sf::Texture m_texture;
};
