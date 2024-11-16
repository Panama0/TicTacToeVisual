#include "ResourceManager.h"

ResMan::ResMan()
{
	PeicesX.reserve(100);
}

void ResMan::loadTiles(const int num, std::string_view path)
{
	for (int i{}; i < num; i++)
	{
		tiles[i].loadTexture(path);
	}
}

void ResMan::addSpr(const char* path)
{
	PeicesX.emplace_back().loadTexture(path);
	PeicesO.emplace_back().loadTexture(path);
}
