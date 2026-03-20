#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <GameAssembly/ProjectileComponent.hpp> 

using namespace TerminaScript;

class WeaponComponent : public TerminaScript::ScriptableComponent {
public:
    WeaponComponent() = default;
    WeaponComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    /*void Start() override;
    void Update(float deltaTime) override;

    void Spawner();*/

private:
    int m_ammo = 20;
    float m_atkSpeedD = 1;
};