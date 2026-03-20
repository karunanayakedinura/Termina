#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
//#include <GameAssembly/>

using namespace TerminaScript;

class PlayerComponent : public TerminaScript::ScriptableComponent{
public:
    PlayerComponent() = default;
    PlayerComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

    void Start()  override;
    void Update(float deltaTime) override;
    void Inspect() override;

    void Move(float speed, float deltaTime);
    void Damage(float damage);
    void AtkDist();
    void AtkCorps();

    // void UpdateCurrentWeapon();
    // bool CanRespawn();

    //////// GETTER & SETTER //////// 
    /*float SetHealth(float newVal);
    float SetSpeed(float newVal);
    float SetShield(float newVal);
    float SetAtkSpeedC(float newVal);
    float SetAtkSpeedD(float newVal);*/

private:
    float m_health = 100;
    float m_speed;
    float m_shield;
    float m_atkC = 30;
    float m_atkD = 15;
    float m_atkSpeedC = 1;
    float m_atkSpeedD = 1;

    int m_weapon = 0;
    bool m_isArmed = false;
    bool m_canRespawn = false;
};