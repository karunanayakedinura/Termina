#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class RangedEnnemyComponent : public ScriptableComponent
{
public:
    RangedEnnemyComponent() = default;
    RangedEnnemyComponent(Termina::Actor* owner)
        : ScriptableComponent(owner) {
    }

    void Start();
    void Update(float deltaTime);
    void OnTriggerEnter(Termina::Actor* other) override;
    void TakeDamage(float value);

private:
    Termina::Actor* m_Player = nullptr;

    float m_Speed = 3.0f;
    float m_MinDistance = 3.0f;
    float m_MaxDistance = 8.0f;

    float m_ShootCooldown = 1.5f;
    float m_Timer = 0.0f;

    float m_Damage = 20.0f;
    int m_Health = 40;
};
