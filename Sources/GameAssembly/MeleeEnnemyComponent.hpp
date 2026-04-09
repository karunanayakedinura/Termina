#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class MeleeEnnemyComponent : public ScriptableComponent
{
public:
    MeleeEnnemyComponent() = default;
    MeleeEnnemyComponent(Termina::Actor* owner)
        : ScriptableComponent(owner) {
    }

    void Start();
    void Update(float deltaTime);
    void OnTriggerEnter(Termina::Actor* other) override;
    void TakeDamage(float value);

private:
    Termina::Actor* m_Player = nullptr;

    float m_Speed = 10.0f;
    float m_AttackRange = 1.5f;
    float m_Damage = 10.0f;

    int m_Health = 60;
};
