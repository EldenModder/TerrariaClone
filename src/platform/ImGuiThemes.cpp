#include "ImGuiThemes.h"
#include "imgui.h"

void ImGuiThemes::SetCatppuccinMochaTheme()
{
    ImVec4* colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_Text] = ImVec4(0.803f, 0.839f, 0.957f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.494f, 0.529f, 0.643f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    colors[ImGuiCol_FrameBg] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.313f, 0.329f, 0.431f, 1.00f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);

    colors[ImGuiCol_MenuBarBg] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.313f, 0.329f, 0.431f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.494f, 0.529f, 0.643f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.537f, 0.705f, 0.980f, 1.00f);

    colors[ImGuiCol_SliderGrab] = ImVec4(0.537f, 0.705f, 0.980f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.729f, 0.580f, 0.980f, 1.00f);

    colors[ImGuiCol_Button] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.313f, 0.329f, 0.431f, 1.00f);

    colors[ImGuiCol_Header] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.313f, 0.329f, 0.431f, 1.00f);

    colors[ImGuiCol_Separator] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.537f, 0.705f, 0.980f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.729f, 0.580f, 0.980f, 1.00f);

    colors[ImGuiCol_ResizeGrip] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.537f, 0.705f, 0.980f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.729f, 0.580f, 0.980f, 1.00f);

    colors[ImGuiCol_Tab] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.537f, 0.705f, 0.980f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.239f, 0.251f, 0.333f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.192f, 0.200f, 0.267f, 1.00f);

    colors[ImGuiCol_DockingPreview] = ImVec4(0.537f, 0.705f, 0.980f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.118f, 0.122f, 0.165f, 1.00f);
}