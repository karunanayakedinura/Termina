#pragma once

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class LoseScreen : public ScriptableComponent
{
public:
    LoseScreen() = default;
    LoseScreen(Termina::Actor* owner)
        : ScriptableComponent(owner) {
    }

    void OnRender(float dt) override;
};