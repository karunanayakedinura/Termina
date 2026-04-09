#include "MainMenuComponent.hpp"

#include <ImGui/imgui.h>
#include <Termina/Core/Application.hpp>
#include <Termina/World/WorldSystem.hpp>

void MainMenuComponent::OnRender(float dt)
{
    ImGuiIO& io = ImGui::GetIO();

    float width = io.DisplaySize.x;
    float height = io.DisplaySize.y;

    // Fenêtre fullscreen
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin("Background", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddRectFilled(
        ImVec2(0, 0),
        io.DisplaySize,
        IM_COL32(0, 0, 0, 255)
    );

    ImGui::End();

    // ==== TITLE ====
    ImGui::SetNextWindowPos(ImVec2(width * 0.5f, height * 0.2f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin("Title", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Last Survivor");

    ImGui::End();

    // ==== PLAY BUTTON ====
    ImGui::SetNextWindowPos(ImVec2(width * 0.5f, height * 0.8f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin("Menu", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Play", ImVec2(200, 50)))
    {
        auto* worldSystem = Termina::Application::GetSystem<Termina::WorldSystem>();

        if (worldSystem)
        {
            worldSystem->LoadWorld(m_WorldToLoad);
            worldSystem->Play();
        }
    }

    ImGui::End();
}