#include "TileResources.h"

void tileResources::loadTiles(const int num, std::string_view path)
{
	for (int i{}; i < num; i++)
	{
		tiles[i].loadTexture(path);
	}
}
