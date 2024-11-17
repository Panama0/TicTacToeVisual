#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"

class Peice
{
public:
	enum class Peices
	{
		empty,
		X,
		O,
		tile,
	};

	Peices corePeice{ Peices::empty };
	
	void load(const char* path);

	sf::Sprite& getSpr() { return m_obj.sprite; };
private:
	GameObj m_obj;
};

