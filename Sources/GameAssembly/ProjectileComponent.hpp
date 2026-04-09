#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include "MeleeEnnemyComponent.hpp"
#include "EnnemyComponent.hpp"
#include "RangedEnnemyComponent.hpp"

namespace GameComponent {
    class ProjectileComponent : public TerminaScript::ScriptableComponent {
    public:
        ProjectileComponent() = default;
        ProjectileComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

        void Start() override;
        void Stop() override;
        void Update(float deltaTime) override;
        void OnTriggerEnter(Termina::Actor* other) override;

    private:
        float m_Speed = 10.f;
        int damage = 20;
    };
}