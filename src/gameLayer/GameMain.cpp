#include <raylib.h>
#include "GameMain.h"
#include <asserts.h>
#include <AssetManager.h>
#include <GameMap.h>
#include <Helpers.h>

struct GameData
{
	GameMap gameMap;
	Camera2D camera;
}gameData;

AssetManager assetManager;

bool InitGame()
{
	assetManager.LoadAll();
	gameData.gameMap.Create(30, 10);

	gameData.gameMap.getBlockUnsafe(0, 0).type = Blocks::dirt;
	gameData.gameMap.getBlockUnsafe(1, 1).type = Blocks::grass;
	gameData.gameMap.getBlockUnsafe(2, 2).type = Blocks::goldBlock;
	gameData.gameMap.getBlockUnsafe(3, 3).type = Blocks::glass;
	gameData.gameMap.getBlockUnsafe(4, 4).type = Blocks::platform;

	//init Camera
	gameData.camera.target = { 0, 0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;

	return true;
}

bool UpdateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
#pragma region Camera Movement
	if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 7.0f * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 7.0f * deltaTime;
	if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 7.0f * deltaTime;
	if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 7.0f * deltaTime;
#pragma endregion

	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldPos.x);
	int blockY = (int)floor(worldPos.y);

	//break block
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b) *b = {};
	}

	//place block
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b) b->type = Blocks::gold;
	}


	BeginMode2D(gameData.camera);

	ClearBackground({ 75, 75, 150, 255 });
	for (int y = 0; y < gameData.gameMap.h; y++)
	{
		for (int x = 0; x < gameData.gameMap.w; x++)
		{
			auto& b = gameData.gameMap.getBlockUnsafe(x, y);
			if (b.type != Blocks::air)
			{

				DrawTexturePro(
					assetManager.textures,
					getTextureAtlas(b.type, 0, 32, 32),
					{ (float)x, (float)y, 1, 1},
					{0, 0},
					0.0f,
					WHITE
				);
			}
		}
	}
	DrawFrameHelpers(assetManager.frame, (float)blockX, (float)blockY);
	EndMode2D();
	return true;
}

void CloseGame()
{

}