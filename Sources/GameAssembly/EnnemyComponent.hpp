#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
using namespace TerminaScript;

class EnnemyComponent : public ScriptableComponent {
public:
    EnnemyComponent() = default;
    EnnemyComponent(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void Start() override;
    void Update(float deltaTime) override;

    void TakeDamage(int amount);

    int GetHealth() const { return m_Health; }

protected:
    int m_Health = 50;
    int m_Damage = 10;
    float m_Speed = 3.0f;
    Termina::Actor* m_Player = nullptr; 

};