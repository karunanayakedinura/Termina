#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <GameAssembly/ProjectileComponent.hpp> 

using namespace TerminaScript;

namespace GameComponent {
    class WeaponComponent : public TerminaScript::ScriptableComponent {
    public:
        WeaponComponent() = default;
        WeaponComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

        void Start() override;
        void Update(float deltaTime) override;
        void Inspect() override;
        void Serialize(nlohmann::json& out) const override;
        void Deserialize(const nlohmann::json& in) override;

        void MunitionSpawner();

    private:
        int m_ID = 1; // si + armes
        int m_Ammo = 20;
        float m_AtkSpeed = 10.f;
        bool m_CanShoot = false;

        float Timer = 1.f;
        float Time;

        TerminaScript::Prefab m_Bullet;
    };
}