#pragma once
#include <raylib.h>

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY);
void DrawFrameHelpers(Texture frameTexture, float blockX, float blockY);