#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <GameAssembly/EnnemyComponent.hpp>

using namespace TerminaScript;

class PlayerComponent : public TerminaScript::ScriptableComponent{
public:
    PlayerComponent() = default;
    PlayerComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start() override;
    void Stop() override;
    void Update(float deltaTime) override;
    void Inspect() override;
    void Serialize(nlohmann::json& out) const override;
    void Deserialize(const nlohmann::json& in) override;

    void Move(float speed, float deltaTime);
    void Damage(float damage);
    void AtkDist(EnnemyComponent& other);
    void AtkCorps(EnnemyComponent& other);

    // void UpdateCurrentWeapon();
    // bool CanRespawn();

    //////// GETTER & SETTER //////// 
    /*float SetHealth(float newVal);
    float SetSpeed(float newVal);
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

    int m_Weapon = 0;
    bool m_IsOn = false;
    bool m_CanRespawn = false;

    EnnemyComponent* m_enemy = nullptr;
};