#pragma once
#include "EnnemyComponent.hpp"

class RangedEnnemyComponent : public EnnemyComponent
{
public:
    RangedEnnemyComponent() = default;
    RangedEnnemyComponent(Termina::Actor* owner) : EnnemyComponent(owner) {}

protected:
    void Attack(float deltaTime) override;
    void Inspect() override;

private:
    float m_ShootCooldown = 1.5f;
    float m_Timer = 0.0f;

    float m_MinDistance = 6.0f; 
    float m_MaxDistance = 12.0f; 
};
