#include "WorldGenerator.h"
#include "RandomStuff.h"
#include <FastNoiseSIMD.h>


void generateWorld(GameMap& gameMap, int seed)
{
	//world size
	const int w = 900;
	const int h = 500;

	//create the map
	gameMap.Create(w, h);

	std::ranlux24_base rng(seed++);

	//desert biomes
	int desertStart = getRandomInt(rng, 10, w - 210);
	int desertEnd = desertStart + 100 + getRandomInt(rng, 0, 100);
	if (desertEnd > w) { desertEnd = w; }

	//noise Gen
	std::unique_ptr<FastNoiseSIMD> dirtNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());
	std::unique_ptr<FastNoiseSIMD> cavesNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());

	//set the seed for the generator
	dirtNoiseGenerator->SetSeed(seed++);
	cavesNoiseGenerator->SetSeed(seed++);

	//configure the noises
	dirtNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
	dirtNoiseGenerator->SetFractalOctaves(6);
	dirtNoiseGenerator->SetFractalGain(0.4f);
	dirtNoiseGenerator->SetFrequency(0.01f);

	cavesNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
	cavesNoiseGenerator->SetFractalOctaves(2);
	cavesNoiseGenerator->SetFrequency(0.02f);

	//generate dirt 1D Noise
	float* dirtNoise = FastNoiseSIMD::GetEmptySet(w);
	dirtNoiseGenerator->FillNoiseSet(dirtNoise, 0, 0, 0, w, 1, 1);

	//normalize
	for (int i = 0; i < w; i++)
	{
		dirtNoise[i] = (dirtNoise[i] + 1) / 2;
	}

	//generate caves 1D Noise
	float* cavesNoise = FastNoiseSIMD::GetEmptySet(w * h);
	cavesNoiseGenerator->FillNoiseSet(cavesNoise, 0, 0, 0, h, w, 1);

	//this is how deep the layer goes
	int dirtOffsetStart = -5;
	int dirtOffsetEnd = 35;

	int keepDirectionTimeStone = getRandomInt(rng, 5, 40);
	int directionStone = getRandomInt(rng, -2, 2);

	int stoneHeight = 90;

	for (int x = 0; x < w; x++)
	{
		bool inDesert = (x >= desertStart && x <= desertEnd);

		
	#pragma region stone height

		keepDirectionTimeStone--;
		if (keepDirectionTimeStone <= 0)
		{
			keepDirectionTimeStone = getRandomInt(rng, 5, 40);
			int directionStone = getRandomInt(rng, -2, 2);
		}

		if (directionStone == -1) if (getRandomChance(rng, 0.25)) stoneHeight--;
		else if (directionStone == -2)
		{
			if (getRandomChance(rng, 0.25)) stoneHeight--;
			if (getRandomChance(rng, 0.25)) stoneHeight--;
		}
		else if (directionStone == 1) if (getRandomChance(rng, 0.25)) stoneHeight++;
		else if (directionStone == 2)
		{
			if (getRandomChance(rng, 0.25)) stoneHeight++;
			if (getRandomChance(rng, 0.25)) stoneHeight++;
		}
		if (stoneHeight < 60) stoneHeight = 60;
		if (stoneHeight > 120) stoneHeight = 120;
	#pragma endregion

		int dirtHeight = dirtOffsetStart + (dirtOffsetEnd - dirtOffsetStart) * dirtNoise[x];
		dirtHeight = stoneHeight - dirtHeight;

		int dirtType = Blocks::dirt;
		int grassType = Blocks::grassBlock;
		int stoneType = Blocks::stone;

		if (inDesert)
		{
			dirtType = Blocks::sand;
			grassType = Blocks::sand;
			stoneType = Blocks::sandStone;
		}

		for (int y = 0; y < h; y++)
		{
			Blocks b;

			if (y > dirtHeight) b.type = dirtType;
			if (y == dirtHeight) b.type = grassType;
			if (y >= stoneHeight) b.type = stoneType;

			if (inDesert)
			{
				int desertMid = (desertStart + desertEnd) / 2;
				int desertHalfWidth = (desertEnd - desertStart) / 2;
				int distFromDesertMid = std::abs(x - desertMid);

				//normalize
				float desertDistance = 1 - distFromDesertMid / float(desertHalfWidth);
				int desertStoneStart = 10 + stoneHeight;
				int desertStoneDepth = 20 + stoneHeight;

				int TriangleStoneY = desertStoneStart + desertDistance + desertStoneDepth;

				//apply stone if below the triangle
				if (y > TriangleStoneY) b.type = Blocks::stone;
			}
			
			gameMap.getBlockUnsafe(x, y) = b;
		}
	}

	//free the data
	FastNoiseSIMD::FreeNoiseSet(dirtNoise);
}
