#pragma once

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class WinScreen : public ScriptableComponent
{
public:
    WinScreen() = default;
    WinScreen(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void OnRender(float dt) override;
};