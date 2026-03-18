#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class PlayerComponent : public TerminaScript::ScriptableComponent
{
public:
    PlayerComponent() = default;
    PlayerComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start()  override;
    void Update(float deltaTime) override;
};