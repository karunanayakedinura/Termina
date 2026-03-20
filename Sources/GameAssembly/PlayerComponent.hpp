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
    float m_maxHealth = 100.f;
    float m_health = 100.f;
    float m_speed;
    float m_shield;
    float m_range;
    float m_atkC = 30.f;
    float m_atkD = 15.f;
    // float m_atkSpeedC = 1;

    int m_weapon = 0;
    bool isOn = false;
    bool m_canRespawn = false;

    EnnemyComponent* m_enemy = nullptr;
};