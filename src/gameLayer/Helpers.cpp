#include "Helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY)
{
	return Rectangle{(float)x * cellSizePixelsX, (float)y * cellSizePixelsY, 
		(float)cellSizePixelsX, (float)cellSizePixelsY};
}

void DrawFrameHelpers(Texture frameTexture, float blockX, float blockY)
{
	DrawTexturePro(
		frameTexture,
		{ 0, 0, (float)frameTexture.width, (float)frameTexture.height },
		{ blockX, blockY, 1, 1 },
		{ 0, 0 },
		0.0f,
		WHITE
	);
}
