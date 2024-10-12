#include "ResourceManager.h"
#include <iostream>

void GameObj::loadTexture(const std::string& path)
{
	if (!m_texture.loadFromFile(path))
	{
		std::cerr << "Could not load file!";
	}
	sprite.setTexture(m_texture);
}