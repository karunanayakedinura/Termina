#include "WeaponComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void WeaponComponent::Start(){}

void WeaponComponent::Update(float deltaTime) {
}

void WeaponComponent::MunitionSpawner(){
	Termina::Actor* bullet = Instantiate(m_BulletPrefab);
	// bullet->GetComponent<Termina::Transform>().SetPosition();
}

void WeaponComponent::Inspect()
{
    ImGui::DragInt("AmmoNB", &m_Ammo, 1, 1, 100);
    ImGui::DragFloat("AtkSpeed", &m_AtkSpeed, 0.1f, 1.f, 100.f);
}

void WeaponComponent::Serialize(nlohmann::json& out) const
{
    out["ID"] = m_ID;
    out["ammo"] = m_Ammo;
    out["atkSpeed"] = m_AtkSpeed;
    out["bulletPrefab"] = m_BulletPrefab.Path;
}

void WeaponComponent::Deserialize(const nlohmann::json& in)
{
    if (in.contains("ID")) m_ID = in["ID"];
    if (in.contains("ammo")) m_Ammo = in["ammo"];
    if (in.contains("atkSpeed")) m_AtkSpeed = in["atkSpeed"];
    if (in.contains("bulletPrefab")) m_BulletPrefab.Path = in["bulletPrefab"];
}