#include "WeaponSpawner.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void GameComponent::WeaponSpawner::Start(){
    m_Gun = TerminaScript::Prefab("Assets/Prefabs/Gun.trp");
    if (!m_Gun.IsValid()) {
        TN_INFO("Gun not loaded");
    }
    
    else{
        Termina::Actor* pistol = Instantiate(m_Gun);
        pistol->GetComponent<Termina::Transform>().SetPosition(this->m_Transform->GetPosition());
        TN_INFO("Spawn Gun");
    }
}

void GameComponent::WeaponSpawner::Update(float deltaTime) {}


void GameComponent::WeaponSpawner::Inspect()
{
    ImGui::DragFloat("AtkSpeed", &m_Timer, 0.1f, 1.f, 100.f);
}

void GameComponent::WeaponSpawner::Serialize(nlohmann::json& out) const
{
    out["timer"] = m_Timer;
}

void GameComponent::WeaponSpawner::Deserialize(const nlohmann::json& in)
{
    if (in.contains("timer")) m_Timer = in["timer"];
}