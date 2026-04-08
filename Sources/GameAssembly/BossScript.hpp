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

    // -------- Gameplay Functions --------
    void EnterPhase(Phase newPhase);
    void DoMeleeAttack();
    void DoRangedAttack();
    void Die();
    void TakeDamage(float amount);

private:
    // -------- References --------
    Termina::Actor* m_PlayerRef = nullptr;
    Termina::Actor* m_IntroParticles = nullptr;

    // -------- Stats --------
    float m_Health = 100.0f;
    float m_MaxHealth = 100.0f;
    float m_Speed = 2.0f;
    float m_MeleeAttackRange = 1.5f;
    float m_RangedAttackRange = 4.0f;
    float m_PrepareRange = 3.0f;

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

    // -------- Death --------
    bool m_IsDead = false;
    float m_DeathTimer = 0.0f;
    float m_DeathDuration = 2.0f;

    // -------- Melee --------
    enum class MeleeState
    {
        None,
        Forward,
        Backward
    };

    MeleeState m_MeleeState = MeleeState::None;
    float m_MeleeTimer = 0.0f;
    float m_MeleeForwardDuration = 0.15f;
    float m_MeleeBackwardDuration = 0.2f;
    float m_MeleeSpeed = 6.0f;

    glm::vec3 m_MeleeDir = glm::vec3(0.0f);

    // -------- Attacks --------
    enum class AttackType
    {
        None,
        MeleeBasic,
        Jump,
        DashCombo,
        Ranged
    };

    AttackType m_CurrentAttack = AttackType::None;
    AttackType m_NextAttack = AttackType::None;

    bool m_IsAttacking = false;
    float m_AttackLocalTimer = 0.0f;

    glm::vec3 m_JumpStartPos = glm::vec3(0.0f);
    glm::vec3 m_JumpTargetPos = glm::vec3(0.0f);
    float m_JumpStartY = 0.0f;

    // -------- Dash Combo --------
    enum class ComboState
    {
        Positioning,
        Dash,
        Check,
        Recovery
    };

    ComboState m_ComboState = ComboState::Positioning;

    int m_ComboStep = 0;
    float m_ComboTimer = 0.0f;

    glm::vec3 m_DashDir = glm::vec3(0.0f);
};