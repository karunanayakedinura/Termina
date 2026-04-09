#include "PlayerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void GameComponent::PlayerComponent::Start(){
    auto* world = m_Owner->GetParentWorld();
    Termina::Actor* gun = world->GetActorByName("Gun");
    m_Weapon = gun;
}

void GameComponent::PlayerComponent::Stop()
{
    m_Enemy = nullptr;
    m_Weapon = nullptr;
}

void GameComponent::PlayerComponent::Update(float deltaTime){
    Move(m_Speed, deltaTime);

    if (Input::IsMouseButtonPressed(Termina::MouseButton::Right)) {
        AtkCorps(*m_Enemy);
    }
    if (Input::IsMouseButtonPressed(Termina::MouseButton::Left)) {
        AtkDist();
    }

    if (m_CanRespawn && m_Health <= 0) {    ///// BUFF
        m_Health = m_MaxHealth / 2;
    }
}

void GameComponent::PlayerComponent::Move(float speed, float deltaTime) {

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

void GameComponent::PlayerComponent::AtkDist() {
    m_Weapon->GetComponent<GameComponent::WeaponComponent>().MunitionSpawner();
}

void GameComponent::PlayerComponent::AtkCorps(Termina::Actor& enemy) {
    //TN_INFO("Atk Corps DONE");
    if(enemy.GetComponent<Termina::Transform>().GetPosition().x < m_Range){
        m_Enemy =  &enemy;
        //m_Enemy.SetHealth(m_Damage);
    }
}

void GameComponent::PlayerComponent::OnTriggerEnter(Termina::Actor* other) {
    /*TN_INFO("Collision");
    if(other->GetName() == "Gun") {
        other->GetComponent<Termina::Transform>().SetPosition(this->m_Transform->GetPosition());       COLLISION BUG (SPAWNER)
        m_Weapon = other;
        m_HasWeapon = true;
    }*/

    //if (other->GetName() == "Enemy") {
    //  SetHealth(other.m_Damage);
    // }

    //if (other->GetName() == "RangeEnemy") {
    //  SetHealth(other.m_Damage);
    // }

    //if (other->GetName() == "MeleeEnemy") {
    //  SetHealth(other.m_Damage);
    // }
}


void GameComponent::PlayerComponent::Inspect()
{
    ImGui::DragFloat("Speed", &m_Speed, 0.5f);
    ImGui::DragFloat("Range", &m_Range, 0.1f, 0.1f, 10.f);
}

void GameComponent::PlayerComponent::Serialize(nlohmann::json& out) const
{
    out["speed"] = m_Speed;
    out["health"] = m_Health;
    out["maxHealth"] = m_MaxHealth;
    out["shield"] = m_Shield;
    out["range"] = m_Range;
    out["atkC"] = m_AtkC;
    out["atkD"] = m_AtkD;
    out["weapon"] = m_WeaponID;
    out["weaponInUse"] = m_WeaponInUse;
    out["canRespawn"] = m_CanRespawn;
    out["hasWeapon"] = m_HasWeapon;
}

void GameComponent::PlayerComponent::Deserialize(const nlohmann::json& in)
{
    if (in.contains("speed"))  m_Speed = in["speed"];
    if (in.contains("health")) m_Health = in["health"];
    if (in.contains("maxHealth")) m_MaxHealth = in["maxHealth"];
    if (in.contains("shield")) m_Shield = in["shield"];
    if (in.contains("range")) m_Range = in["range"];
    if (in.contains("atkC")) m_AtkC = in["atkC"];
    if (in.contains("atkD")) m_AtkD = in["atkD"];
    if (in.contains("weapon")) m_WeaponID = in["weapon"];
    if (in.contains("weaponInUse")) m_WeaponInUse = in["weaponInUse"];
    if (in.contains("canRespawn")) m_CanRespawn = in["canRespawn"];
    if (in.contains("hasWeapon")) m_HasWeapon = in["hasWeapon"];
}
