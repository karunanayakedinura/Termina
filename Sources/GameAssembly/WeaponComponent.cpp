#include "WeaponComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void GameComponent::WeaponComponent::Start(){
    m_Bullet = TerminaScript::Prefab("Assets/Prefabs/BulletPrefab.trp");
    if (!m_Bullet.IsValid())
        TN_INFO("Bullet not loaded");
}

void GameComponent::WeaponComponent::Update(float deltaTime) {
    if (Time >= Timer && m_Ammo > 0) {
        m_CanShoot = true;
        m_Ammo -= 1;
    }
    else {
        Time += deltaTime;
    }
}

void GameComponent::WeaponComponent::MunitionSpawner(){
    if (m_CanShoot){
        Termina::Actor* bullet = Instantiate(m_Bullet);
        bullet->GetComponent<Termina::Transform>().SetPosition(this->m_Transform->GetPosition());
        m_CanShoot = false;
        Time = 0.f;
    }
}

void GameComponent::WeaponComponent::Inspect()
{
    ImGui::DragInt("AmmoNB", &m_Ammo, 1, 1, 100);
    ImGui::DragFloat("AtkSpeed", &m_AtkSpeed, 0.1f, 1.f, 100.f);
}

void GameComponent::WeaponComponent::Serialize(nlohmann::json& out) const
{
    out["ID"] = m_ID;
    out["ammo"] = m_Ammo;
    out["atkSpeed"] = m_AtkSpeed;
}

void GameComponent::WeaponComponent::Deserialize(const nlohmann::json& in)
{
    if (in.contains("ID")) m_ID = in["ID"];
    if (in.contains("ammo")) m_Ammo = in["ammo"];
    if (in.contains("atkSpeed")) m_AtkSpeed = in["atkSpeed"];
}