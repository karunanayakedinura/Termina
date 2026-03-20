#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

class ProjectileComponent : public TerminaScript::ScriptableComponent {
public:
    ProjectileComponent() = default;
    ProjectileComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    /*void Start() override;
    void Update(float deltaTime) override;*/

private:
    float m_speed;
};