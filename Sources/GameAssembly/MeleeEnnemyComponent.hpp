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

    void Attack(float deltaTime);

private:
    Termina::Actor* m_Player = nullptr;
    float m_Damage = 10.0f;
};
