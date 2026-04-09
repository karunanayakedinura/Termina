#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class GunPos : public ScriptableComponent
{
public:
    GunPos() = default;
    GunPos(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void Start() override;
    void Update(float deltaTime) override;

private:

    Termina::Actor* m_Player = nullptr;
};

