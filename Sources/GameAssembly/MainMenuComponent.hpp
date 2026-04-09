#pragma once

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class MainMenuComponent : public ScriptableComponent
{
public:
    MainMenuComponent() = default;
    MainMenuComponent(Termina::Actor* owner)
        : ScriptableComponent(owner) {
    }

    void OnRender(float dt) override;

private:
    std::string m_WorldToLoad = "Assets/Worlds/GameWorld.trw";
};