#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <glm/glm.hpp>

class BossScript : public TerminaScript::ScriptableComponent
{
public:
    BossScript() = default;
    BossScript(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void Start() override;
    void Update(float deltaTime) override;
    void Inspect() override;

    void Serialize(nlohmann::json& out) const override;
    void Deserialize(const nlohmann::json& in) override;

    float GetAttackRangeSq() const;

private:
    Termina::Actor* m_PlayerRef = nullptr;
    Termina::Actor* m_IntroParticles = nullptr;

    enum class Phase
    {
        Intro,
        Phase1, // full melee
        Phase2, // alternate melee/range
        Phase3, // full range + overheal
        Phase4  // ultra hard
    };

    enum class State
    {
        Idle,
        Move,
        Attack
    };

    // -------- Stats --------
    float m_Health = 100.0f;
    float m_MaxHealth = 100.0f;
    float m_Speed = 1.0f;
    float m_MeleeAttackRange = 0.5f;
    float m_RangedAttackRange = 4.0f;

    // -------- State --------
    Phase m_CurrentPhase = Phase::Intro;
    State m_CurrentAction = State::Idle;

    // -------- Intro --------
    bool m_IntroDropDone = false;
    bool m_IntroWaitDone = false;
    float m_IntroStartHeight = 50.0f;
    float m_IntroEndHeight = 1.2f;
    float m_IntroTimer = 0.0f;
    float m_IntroDropDuration = 1.0f;
    float m_IntroWaitDuration = 3.0f;

    // -------- Timers --------
    float m_AttackTimer = 0.0f;
    float m_AttackCooldown = 1.5f;

    bool m_UseMelee = true;
    float m_AttackSwitchTimer = 0.0f;
    float m_AttackSwitchCooldown = 2.0f;

    bool m_InTransition = false;
    float m_PhaseTransitionTimer = 0.0f;
};