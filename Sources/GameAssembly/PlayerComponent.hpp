#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class PlayerComponent : public TerminaScript::ScriptableComponent{
public:
    PlayerComponent() = default;
    PlayerComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start()  override;
    void Update(float deltaTime) override;

    void SetHealth(float value) { health = value; }
    void SetDead(bool value) { isDead = value; }

    
private:
    float health = 100;
    float speed = 1;
    float shield = 0;
    float atkSpeedC = 1;
    float atkSpeedD = 1;

    int weapon = 0;
    bool isDead = false;
    bool isArmed = false;
    bool canRespawn = false;
};