#pragma once
#include "EnnemyComponent.hpp"

class MeleeEnnemyComponent : public EnnemyComponent
{
public:
    MeleeEnnemyComponent() = default;
    MeleeEnnemyComponent(Termina::Actor* owner) : EnnemyComponent(owner) {}

protected:
    void Attack(float deltaTime) override;
};
