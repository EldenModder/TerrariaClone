#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <ImGuiThemes.h> 
#include <GameMain.h>

int main(void)
{
	ImGuiThemes imguiThemes;
#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE); // no log output to the console by raylib
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1200, 720, "raylib");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);
	
#pragma region ImGui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 1.5f;
	imguiThemes.SetCatppuccinMochaTheme();
#pragma endregion

	if (!InitGame())
	{
		return 0;
	}
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground({ 75, 75, 150, 255 });
#pragma region ImGui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
#pragma endregion

		if (!UpdateGame())
		{
			CloseWindow();
		}

		rlImGuiEnd();
		EndDrawing();
	}

	CloseWindow();
	CloseGame();
	
	rlImGuiShutdown();

	return 0;
}