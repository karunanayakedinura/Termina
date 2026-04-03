#include "PlayerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void PlayerComponent::Start()
{
    // bloquer la cam.
}

void PlayerComponent::Stop()
{
    m_Enemy = nullptr;
}

void PlayerComponent::Update(float deltaTime){
    Move(m_Speed, deltaTime);

    /*if (Input::IsMouseButtonPressed(Termina::MouseButton::Left)) {
        switch (m_WeaponInUse) {
        case 0:
            AtkCorps(*m_enemy);
            break;

        case 1: /// CD?
            AtkDist();
            break;
        }
    }*/

    if (m_CanRespawn && m_Health <= 0) {
        m_Health = m_MaxHealth / 2;
    }
}

void PlayerComponent::Move(float speed, float deltaTime) {

    glm::vec3 pos = m_Transform->GetPosition();
    if (Input::IsKeyHeld(Termina::Key::Up)) {
        pos += glm::vec3(0.f, 0.f, -speed) * deltaTime;
    }
    if (Input::IsKeyHeld(Termina::Key::Left)) {
        pos += glm::vec3(-speed, 0.f, 0.f) * deltaTime;
    }
    if (Input::IsKeyHeld(Termina::Key::Down)) {
        pos += glm::vec3(0.f, 0.f, speed) * deltaTime;
    }
    if (Input::IsKeyHeld(Termina::Key::Right)) {
        pos += glm::vec3(speed, 0.f, 0.f) * deltaTime;
    }
    m_Transform->SetPosition(pos);
}

void PlayerComponent::AtkDist() {
    m_Weapon->MunitionSpawner();
}

void PlayerComponent::AtkCorps(EnnemyComponent& enemy) {
    if(enemy.GetOwner()->GetComponent<Termina::Transform>().GetPosition().x < m_Range){
        m_Enemy =  &enemy;
        //m_Enemy.SetHealth(m_Damage);
    }
}


void PlayerComponent::Inspect()
{
    ImGui::DragFloat("Speed", &m_Speed, 0.5f);
    ImGui::DragFloat("Range", &m_Range, 0.1f, 0.1f, 10.f);
}

void PlayerComponent::Serialize(nlohmann::json& out) const
{
    out["speed"] = m_Speed;
    out["health"] = m_Health;
    out["maxHealth"] = m_MaxHealth;
    out["shield"] = m_Shield;
    out["range"] = m_Range;
    out["atkC"] = m_AtkC;
    out["atkD"] = m_AtkD;
    out["weapon"] = m_WeaponID;
    out["isOn"] = m_IsOn;
    out["canRespawn"] = m_CanRespawn;
}

void PlayerComponent::Deserialize(const nlohmann::json& in)
{
    if (in.contains("speed"))  m_Speed = in["speed"];
    if (in.contains("health")) m_Health = in["health"];
    if (in.contains("maxHealth")) m_MaxHealth = in["maxHealth"];
    if (in.contains("shield")) m_Shield = in["shield"];
    if (in.contains("range")) m_Range = in["range"];
    if (in.contains("atkC")) m_AtkC = in["atkC"];
    if (in.contains("atkD")) m_AtkD = in["atkD"];
    if (in.contains("weapon")) m_WeaponID = in["weapon"];
    if (in.contains("isOn")) m_IsOn = in["isOn"];
    if (in.contains("canRespawn")) m_CanRespawn = in["canRespawn"];
}
