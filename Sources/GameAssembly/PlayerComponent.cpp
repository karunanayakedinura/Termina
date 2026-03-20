#include "PlayerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void PlayerComponent::Start()
{
    // Called once when the scene starts playing.
}

void PlayerComponent::Update(float deltaTime)
{
    Move(m_speed, deltaTime);
}

void PlayerComponent::Move(float speed, float deltaTime) {

    glm::vec3 pos = m_Transform->GetPosition();

    if (Input::IsKeyPressed(Termina::Key::Z)) {
        pos += glm::vec3(speed, 0, 0) * deltaTime;
        m_Transform->SetPosition(pos);
    }
    if (Input::IsKeyPressed(Termina::Key::Q)) {
        pos += glm::vec3(0, -speed, 0) * deltaTime;
        m_Transform->SetPosition(pos);
    }
    if (Input::IsKeyPressed(Termina::Key::S)) {
        pos += glm::vec3(0, 0, -speed) * deltaTime;
        m_Transform->SetPosition(pos);
    }
    if (Input::IsKeyPressed(Termina::Key::D)) {
        pos += glm::vec3(0, 0, speed) * deltaTime;
        m_Transform->SetPosition(pos);
    }
}

void PlayerComponent::Inspect()
{
    ImGui::DragFloat("Speed", &m_speed, 1.f, 0.5f, 100.f);
}

void PlayerComponent::Damage(float damage) {
    m_health -= damage;
}

void PlayerComponent::AtkDist() {
    if () {

    }
}

void PlayerComponent::AtkCorps() {

}