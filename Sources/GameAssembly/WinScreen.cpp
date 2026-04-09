#include "WinScreen.hpp"

#include <ImGui/imgui.h>
#include <Termina/Core/Application.hpp>
#include <Termina/World/WorldSystem.hpp>

#include "GameManagerComponent.hpp"

void WinScreen::OnRender(float dt)
{
    auto* gm = GameManagerComponent::Instance;
    if (!gm || !gm->IsGameOver() || !gm->HasWon())
        return;

    ImGuiIO& io = ImGui::GetIO();

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    draw->AddRectFilled(ImVec2(0, 0), io.DisplaySize, IM_COL32(0, 0, 0, 200));

    ImGui::SetNextWindowPos(
        ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
        ImGuiCond_Always,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::Begin("Win", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("YOU WIN!");

    if (ImGui::Button("Menu"))
    {
        auto* ws = Termina::Application::GetSystem<Termina::WorldSystem>();
        if (ws)
            ws->RequestSceneTransition("Assets/Worlds/MainMenu.trw");
    }

    ImGui::End();
}