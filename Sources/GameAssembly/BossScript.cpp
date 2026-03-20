#include "BossScript.hpp"
#include "ParticleSystem.hpp"
#include <ImGui/imgui.h>
#include <Termina/Core/Logger.hpp>

void BossScript::Start()
{
    m_PlayerRef = m_Owner->GetParentWorld()->GetActorByName("PlayerTest");
    m_IntroParticles = m_Owner->GetParentWorld()->GetActorByName("ParticuleBossIntro");

    if (!m_PlayerRef)
        TN_WARN("BossScript: Player not found in scene!");

    if (!m_IntroParticles)
        TN_WARN("BossScript: IntroParticles not found in scene!");
}

void BossScript::Update(float deltaTime)
{
    if (!m_PlayerRef)
        return;

    // -------- INTRO --------
    if (m_CurrentPhase == Phase::Intro)
    {
        m_IntroTimer += deltaTime;
        glm::vec3 bossPos = m_Transform->GetPosition();
        glm::vec3 particlePos = bossPos;
        particlePos.y -= 1.2f; // particle offset

        // --- DROP FROM THE SKY ---
        if (!m_IntroDropDone)
        {
            float t = glm::clamp(m_IntroTimer / m_IntroDropDuration, 0.0f, 1.0f);
            float easeOutT = 1.0f - pow(1.0f - t, 3); // cubic ease-out
            bossPos.y = glm::mix(m_IntroStartHeight, m_IntroEndHeight, easeOutT);
            m_Transform->SetPosition(bossPos);

            if (m_IntroParticles)
            {
                auto& psXform = m_IntroParticles->GetComponent<Termina::Transform>();
                psXform.SetPosition(particlePos);
            }

            if (t >= 1.0f)
            {
                m_IntroDropDone = true;
                m_IntroTimer = 0.0f;
            }

            return;
        }

        // --- WAIT AT LANDING POSITION ---
        if (!m_IntroWaitDone)
        {
            bossPos.y = m_IntroEndHeight;
            m_Transform->SetPosition(bossPos);

            if (m_IntroParticles)
            {
                auto& ps = m_IntroParticles->GetComponent<ParticleSystemComponent>();
                auto& psXform = m_IntroParticles->GetComponent<Termina::Transform>();
                psXform.SetPosition(particlePos);
                ps.m_EmitRate = 150.0f;
            }

            if (m_IntroTimer >= m_IntroWaitDuration)
            {
                m_IntroWaitDone = true;
                m_CurrentPhase = Phase::Phase1;

                if (m_IntroParticles)
                {
                    auto& ps = m_IntroParticles->GetComponent<ParticleSystemComponent>();
                    ps.m_EmitRate = 0.0f;
                }
            }
            return;
        }
    }

    // --- TIMERS ---
    m_AttackTimer -= deltaTime;
    if (m_InTransition)
    {
        m_PhaseTransitionTimer -= deltaTime;
        if (m_PhaseTransitionTimer <= 0.0f)
            m_InTransition = false;
        return;
    }

    // --- PHASE LOGIC ---
    float hpPercent = m_Health / m_MaxHealth;
    switch (m_CurrentPhase)
    {
    case Phase::Phase1:
        if (hpPercent <= 0.5f)
            m_CurrentPhase = Phase::Phase2;
        break;
    case Phase::Phase2:
        if (hpPercent <= 0.1f)
        {
            m_CurrentPhase = Phase::Phase3;
            m_MaxHealth = 125.0f;
            m_Health = m_MaxHealth;
            m_InTransition = true;
            m_PhaseTransitionTimer = 2.0f;
            m_UseMelee = false;
        }
        break;
    case Phase::Phase3:
        if (hpPercent <= 0.5f)
            m_CurrentPhase = Phase::Phase4;
        break;
    case Phase::Phase4:
        break;
    default:
        break;
    }

    // --- POSITION AND DIRECTION ---
    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_PlayerRef->GetComponent<Termina::Transform>().GetPosition();
    glm::vec3 dir = target - pos;
    dir.y = 0.0f;
    float distSq = glm::dot(dir, dir);

    // --- STATE MACHINE ---
    float attackRangeSq = GetAttackRangeSq();
    switch (m_CurrentAction)
    {
    case State::Idle:
        m_CurrentAction = (distSq <= attackRangeSq) ? State::Attack : State::Move;
        break;
    case State::Move:
        if (distSq <= attackRangeSq) m_CurrentAction = State::Attack;
        break;
    case State::Attack:
        if (distSq > attackRangeSq) m_CurrentAction = State::Move;
        break;
    }

    // -------- BEHAVIOR: MOVE FORWARD/BACKWARD --------
    float speedMultiplier = (m_CurrentPhase == Phase::Phase4) ? 1.8f : 1.0f;

    // Determine ideal distance based on phase and attack type
    float idealDistance = 0.0f;
    switch (m_CurrentPhase)
    {
    case Phase::Phase1: // full melee
        idealDistance = m_MeleeAttackRange * 0.8f;
        break;
    case Phase::Phase2: // alternate melee/ranged
        idealDistance = m_UseMelee ? m_MeleeAttackRange * 0.8f : m_RangedAttackRange * 0.7f;
        break;
    case Phase::Phase3: // full ranged
        idealDistance = m_RangedAttackRange * 0.7f;
        break;
    case Phase::Phase4: // hardcore
        idealDistance = m_UseMelee ? m_MeleeAttackRange * 0.8f : m_RangedAttackRange * 0.7f;
        break;
    default:
        idealDistance = m_MeleeAttackRange * 0.8f;
        break;
    }

    float dist = glm::length(dir);

    if (dist > 0.0001f)
    {
        glm::vec3 moveDir = glm::normalize(dir);

        // --- MOVE FORWARD / BACKWARD ---
        if (dist > idealDistance + 0.1f) // too far -> move forward
        {
            pos += moveDir * m_Speed * deltaTime;
            m_CurrentAction = State::Move;
        }
        else if (dist < idealDistance - 0.1f) // too close -> move backward
        {
            pos -= moveDir * m_Speed * deltaTime;
            m_CurrentAction = State::Move;
        }
        else
        {
            // correct distance -> attack
            m_CurrentAction = State::Attack;
        }

        m_Transform->SetPosition(pos);
    }

    // --- ATTACK ---
    if (m_CurrentAction == State::Attack && m_AttackTimer <= 0.0f)
    {
        switch (m_CurrentPhase)
        {
        case Phase::Phase1: // FULL MELEE
            m_AttackTimer = 2.0f;
            break;
        case Phase::Phase2: // ALTERNATE
            m_AttackSwitchTimer -= deltaTime;
            if (m_AttackSwitchTimer <= 0.0f)
            {
                m_UseMelee = !m_UseMelee;
                m_AttackSwitchTimer = 2.0f;
            }
            m_AttackTimer = m_UseMelee ? 2.0f : 1.5f;
            break;
        case Phase::Phase3: // FULL RANGE
            m_AttackTimer = 1.2f;
            break;
        case Phase::Phase4: // HARDCORE
            m_AttackSwitchTimer -= deltaTime * speedMultiplier;
            if (m_AttackSwitchTimer <= 0.0f)
            {
                m_UseMelee = !m_UseMelee;
                m_AttackSwitchTimer = 1.5f;
            }
            m_AttackTimer = m_UseMelee ? 1.0f : 0.8f;
            break;
        default:
            break;
        }
    }

    // -------- ROTATION --------
    if (distSq > 0.0001f)
    {
        glm::vec3 lookDir = -glm::normalize(dir);
        float angle = atan2(lookDir.x, lookDir.z);
        glm::quat targetRot = glm::angleAxis(angle, glm::vec3(0, 1, 0));
        glm::quat smoothRot = glm::slerp(m_Transform->GetRotation(), targetRot, 5.0f * deltaTime);
        m_Transform->SetRotation(smoothRot);
    }
}

void BossScript::Inspect()
{
    ImGui::DragFloat("Health", &m_Health, 1.0f, 0.0f, 10000.0f);
    ImGui::DragFloat("Max Health", &m_MaxHealth, 1.0f, 1.0f, 10000.0f);
    ImGui::DragFloat("Speed", &m_Speed, 0.1f, 0.0f, 100.0f);
    ImGui::DragFloat("Melee Range", &m_MeleeAttackRange, 0.1f, 0.1f, 100.0f);
    ImGui::DragFloat("Ranged Range", &m_RangedAttackRange, 0.1f, 0.1f, 100.0f);
    ImGui::Text("Phase: %d", (int)m_CurrentPhase);
    ImGui::Text("State: %d", (int)m_CurrentAction);
    ImGui::Text("HP: %.1f / %.1f", m_Health, m_MaxHealth);
}

void BossScript::Serialize(nlohmann::json& out) const
{
    out["health"] = m_Health;
    out["max_health"] = m_MaxHealth;
    out["speed"] = m_Speed;
    out["melee_range"] = m_MeleeAttackRange;
    out["ranged_range"] = m_RangedAttackRange;
    out["phase"] = static_cast<int>(m_CurrentPhase);
}

void BossScript::Deserialize(const nlohmann::json& in)
{
    if (in.contains("health"))        m_Health = in["health"];
    if (in.contains("max_health"))    m_MaxHealth = in["max_health"];
    if (in.contains("speed"))         m_Speed = in["speed"];
    if (in.contains("melee_range"))   m_MeleeAttackRange = in["melee_range"];
    if (in.contains("ranged_range"))  m_RangedAttackRange = in["ranged_range"];
    if (in.contains("phase"))         m_CurrentPhase = static_cast<Phase>(in["phase"]);
}

// --- ATTACK RANGE HELPER ---
float BossScript::GetAttackRangeSq() const
{
    switch (m_CurrentPhase)
    {
    case Phase::Phase1: return m_MeleeAttackRange * m_MeleeAttackRange;
    case Phase::Phase2: return m_UseMelee ? m_MeleeAttackRange * m_MeleeAttackRange
        : m_RangedAttackRange * m_RangedAttackRange;
    case Phase::Phase3: return m_RangedAttackRange * m_RangedAttackRange;
    case Phase::Phase4: return m_UseMelee ? m_MeleeAttackRange * m_MeleeAttackRange
        : m_RangedAttackRange * m_RangedAttackRange;
    default: return 0.0f;
    }
}