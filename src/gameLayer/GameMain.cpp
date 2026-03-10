#include "GameMain.h"
#include <raylib.h>
#include <asserts.h>
#include <AssetManager.h>
#include <GameMap.h>
#include <Helpers.h>
#include <raymath.h>
#include <WorldGenerator.h>
#include <imgui.h>>

struct GameData
{
	GameMap gameMap;
	Camera2D camera;
}gameData;

AssetManager assetManager;

bool InitGame()
{
	assetManager.LoadAll();
	
	generateWorld(gameData.gameMap);

	//init Camera
	gameData.camera.target = { 20, 120 };
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
	static float CAMERA_SPEED = 10;
	if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= CAMERA_SPEED * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += CAMERA_SPEED * deltaTime;
	if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= CAMERA_SPEED * deltaTime;
	if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += CAMERA_SPEED * deltaTime;
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

#pragma region smallWorldRenderingOptimization
	Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ 
		(float)GetScreenWidth(),
		(float)GetScreenHeight()}, 
		gameData.camera
	);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.y + 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);

	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);

#pragma endregion

	for (int y = startYView; y <= endYView; y++)
	{
		for (int x = startXView; x <= endXView; x++)
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

#pragma region ImGui
	ImGui::Begin("Game Controls");

	ImGui::SliderFloat("Camera zoom:", &gameData.camera.zoom, 1, 150);
	ImGui::SliderFloat("Camera speed:", &CAMERA_SPEED, 5, 60);

	ImGui::End();
#pragma endregion


	DrawFPS(10, 10);
	return true;
}

void CloseGame()
{

}