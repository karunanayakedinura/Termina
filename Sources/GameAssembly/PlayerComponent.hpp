#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <GameAssembly/EnnemyComponent.hpp>
#include "WeaponComponent.hpp"
#include "WeaponSpawner.hpp"

using namespace TerminaScript;

namespace GameComponent {
    class PlayerComponent : public TerminaScript::ScriptableComponent {
    public:
        PlayerComponent() = default;
        PlayerComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

        void Start() override;
        void Stop() override;
        void Update(float deltaTime) override;

        void Move(float speed, float deltaTime);
        void AtkDist();
        void AtkCorps(Termina::Actor& other);
        void OnTriggerEnter(Termina::Actor* other) override;

        void Inspect() override;
        void Serialize(nlohmann::json& out) const override;
        void Deserialize(const nlohmann::json& in) override;

        // void UpdateCurrentWeapon();
        // bool CanRespawn();

        //////// GETTER & SETTER //////// 
        float SetHealth(float newVal) { return m_Health -= newVal; };
        /*float SetSpeed(float newVal);
        float SetShield(float newVal);
        float SetAtkSpeedC(float newVal);
        float SetAtkSpeedD(float newVal);*/

    private:
        float m_MaxHealth = 100.f;
        float m_Health = 100.f;
        float m_Speed = 1.f;
        float m_Shield;
        float m_Range;
        float m_AtkC = 30.f;
        float m_AtkD = 15.f;
        float m_Damage = 10.f;

        int m_WeaponID = 0; // Si + armes
        bool m_HasWeapon = false;
        bool m_WeaponInUse = false;
        bool m_CanRespawn = false;

        TerminaScript::Prefab m_Gun;
        Termina::Actor* m_Weapon = nullptr;
        Termina::Actor* m_Enemy = nullptr;
    };
}