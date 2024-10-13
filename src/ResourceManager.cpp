#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <string_view>
#include <optional>


void GameObj::loadTexture(std::string_view path)
{
	if (!m_texture.loadFromFile(path.data()))
	{
		std::cerr << "Could not load file!";
	}
	sprite.setTexture(m_texture);
}

void ResMan::loadTiles(const int num, std::string_view path)
{
	for (int i{}; i < num; i++)
	{
		tiles[i].loadTexture(path);
	}
}