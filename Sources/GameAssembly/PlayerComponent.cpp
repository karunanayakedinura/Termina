#include "PlayerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void PlayerComponent::Start()
{
    // Called once when the scene starts playing.
}

void PlayerComponent::Stop()
{
    m_enemy = nullptr;
}

void PlayerComponent::Update(float deltaTime){
    Move(1.0f, deltaTime);

    /*if (Input::IsMouseButtonPressed(Termina::MouseButton::Left)) {
        switch (m_weapon) {
        case 0:
            AtkCorps(*m_enemy);
            break;

        case 1:
            AtkDist(*m_enemy);
            break;
        }
    }*/

    if (m_canRespawn && m_health <= 0) {
        m_health = m_maxHealth;
    }
}

void PlayerComponent::Move(float speed, float deltaTime) {

    glm::vec3 pos = m_Transform->GetPosition();
    //

    if (Input::IsKeyPressed(Termina::Key::Z)) {
        TN_INFO("pos initial %a", pos);
        pos += glm::vec3(speed, 0, 0) * deltaTime;
        TN_INFO("pos update %a", pos);
    }
    if (Input::IsKeyPressed(Termina::Key::Q)) {
        pos += glm::vec3(0, -speed, 0) * deltaTime;
    }
    if (Input::IsKeyPressed(Termina::Key::S)) {
        pos += glm::vec3(0, 0, -speed) * deltaTime;
    }
    if (Input::IsKeyPressed(Termina::Key::D)) {
        pos += glm::vec3(0, 0, speed) * deltaTime;
    }
    m_Transform->SetPosition(pos);
}

void PlayerComponent::Damage(float damage) {
    m_health -= damage;
}

void PlayerComponent::AtkDist(EnnemyComponent& other) {
    // Appel de spawn de projectile(s)
}

void PlayerComponent::AtkCorps(EnnemyComponent& other) {
    if(other.GetOwner()->GetComponent<Termina::Transform>().GetPosition().x < m_range){
        m_enemy =  &other;
        // other.SetHealth(damage);
    }
}


void PlayerComponent::Inspect()
{
    ImGui::DragFloat("Speed", &m_speed, 1.f, 0.5f, 100.f);
    ImGui::DragFloat("Range", &m_range, 0.1f, 0.1f, 10.f);
}
