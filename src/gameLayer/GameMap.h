#pragma once
#include <vector>
#include <blocks.h>

struct GameMap
{
	int w = 0;
	int h = 0;

	std::vector<Blocks> mapData;

	void Create(int w, int h);

	Blocks& getBlockUnsafe(int x, int y);
	
	//check if we didn't get outside the map boundary and return a null pointer if so
	Blocks* getBlockSafe(int x, int y);
};