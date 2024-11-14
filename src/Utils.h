#pragma once
#include <iostream>
#include "SFML/Graphics.hpp" //for vector


sf::Vector2i remap1Dto2D(int index)
{
	const int remap[9][2] = { {0,0}, {0,1}, {0,2},
							  {1,0}, {1,1}, {1,2},
							  {2,0}, {2,1}, {2,2} };
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