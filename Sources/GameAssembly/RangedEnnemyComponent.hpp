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

    void Attack(float deltaTime);

private:
    Termina::Actor* m_Player = nullptr;

    float m_Speed = 2.0f;
    float m_MinDistance = 3.0f;
    float m_MaxDistance = 8.0f;

    float m_ShootCooldown = 1.5f;
    float m_Timer = 0.0f;
};
