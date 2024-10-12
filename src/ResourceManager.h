#pragma once
#include "SFML/Graphics.hpp"


class GameObj
{
public:
	sf::Sprite sprite;

	void loadTexture(const std::string& path);
private:
	sf::Texture m_texture;
};