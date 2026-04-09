#include "LoseScreen.hpp"
#include "PlayerComponent.hpp"

#include <ImGui/imgui.h>
#include <Termina/Core/Application.hpp>
#include <Termina/World/WorldSystem.hpp>

#include "GameManagerComponent.hpp"

void LoseScreen::OnRender(float dt)
{
    auto* gm = GameManagerComponent::Instance;
    if (!gm || !gm->IsGameOver() || gm->HasWon())
        return;

    ImGuiIO& io = ImGui::GetIO();

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    draw->AddRectFilled(ImVec2(0, 0), io.DisplaySize, IM_COL32(0, 0, 0, 200));

    ImGui::SetNextWindowPos(
        ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
        ImGuiCond_Always,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::Begin("Lose", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("YOU LOSE!");

    if (ImGui::Button("Retry"))
    {
        auto* ws = Termina::Application::GetSystem<Termina::WorldSystem>();
        if (ws && ws->GetCurrentWorld())
        {
            auto* player = ws->GetCurrentWorld()->GetActorByName("Player");
            if (player)
            {
                auto& pc = player->GetComponent<PlayerComponent>();
                pc.SetHealth(100.0f);
                pc.SetDead(false);
            }

            // Recharge la scène pour réinitialiser tout
            ws->RequestSceneTransition("Assets/Worlds/GameWorld.trw");
        }
    }

    ImGui::End();
}
 