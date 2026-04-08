#include "BossScript.hpp"
#include "ParticleSystem.hpp"
#include <ImGui/imgui.h>
#include <Termina/Core/Logger.hpp>

void BossScript::Start()
{
    m_PlayerRef = m_Owner->GetParentWorld()->GetActorByName("PlayerTest");
    m_IntroParticles = m_Owner->GetParentWorld()->GetActorByName("ParticuleBossIntro");

    m_AttackSwitchTimer = m_AttackSwitchCooldown;

    if (!m_PlayerRef)
        TN_WARN("BossScript: Player not found in scene!");

    if (!m_IntroParticles)
        TN_WARN("BossScript: IntroParticles not found in scene!");
}

void BossScript::Update(float deltaTime)
{
    if (!m_PlayerRef)
        return;

    // -------- DEATH CHECK --------
    if (!m_IsDead && m_Health <= 0.0f)
        Die();

    if (m_IsDead)
    {
        m_DeathTimer -= deltaTime;

        glm::vec3 pos = m_Transform->GetPosition();

        if (m_DeathTimer > 0.0f) 
        {
            pos.y += deltaTime * 0.5f;
            m_Transform->SetPosition(pos);

            if (m_IntroParticles)
            {
                glm::vec3 bossPos = m_Transform->GetPosition();
                glm::vec3 particlePos = bossPos;

                auto& psXform = m_IntroParticles->GetComponent<Termina::Transform>();
                psXform.SetPosition(particlePos);

                auto& ps = m_IntroParticles->GetComponent<ParticleSystemComponent>();
                ps.m_EmitRate = 5.0f;
            }
        }

        if (m_DeathTimer <= 0.0f)
        {
            pos.y = -100.0f;
            m_Transform->SetPosition(pos);

            if (m_IntroParticles)
            {
                auto& ps = m_IntroParticles->GetComponent<ParticleSystemComponent>();
                ps.m_EmitRate = 0.0f;
            }
        }

        return;
    }

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
                EnterPhase(Phase::Phase1);

                if (m_IntroParticles)
                {
                    auto& ps = m_IntroParticles->GetComponent<ParticleSystemComponent>();
                    ps.m_EmitRate = 0.0f;
                }
            }
            return;
        }
    }

    // -------- ATTACK RUNNING --------
    if (m_IsAttacking)
    {
        m_AttackLocalTimer += deltaTime;

        switch (m_CurrentAttack)
        {

        case AttackType::MeleeBasic:
        {
            glm::vec3 pos = m_Transform->GetPosition();

            if (m_MeleeState == MeleeState::Forward)
            {
                pos += m_MeleeDir * 8.0f * deltaTime;

                m_MeleeTimer -= deltaTime;
                if (m_MeleeTimer <= 0.0f)
                {
                    m_MeleeState = MeleeState::Backward;
                    m_MeleeTimer = 0.25f;
                }
            }
            else if (m_MeleeState == MeleeState::Backward)
            {
                pos -= m_MeleeDir * 6.0f * deltaTime;

                m_MeleeTimer -= deltaTime;
                if (m_MeleeTimer <= 0.0f)
                {
                    m_IsAttacking = false;
                    m_CurrentAttack = AttackType::None;
                }
            }

            m_Transform->SetPosition(pos);
            break;
        }

        case AttackType::Jump:
        {
            glm::vec3 pos = m_Transform->GetPosition();

            float t = m_AttackLocalTimer;

            if (t < 0.2f)
            {
                pos = m_JumpStartPos;
                pos.y = m_JumpStartY - 0.3f;
            }
            else if (t < 0.6f)
            {
                float jt = (t - 0.2f) / 0.4f;
                jt = glm::clamp(jt, 0.0f, 1.0f);

                glm::vec3 flat = glm::mix(m_JumpStartPos, m_JumpTargetPos, jt);

                float height = 4.0f;
                flat.y = m_JumpStartY + height * (4.0f * jt * (1.0f - jt));

                pos = flat;
            }
            else if (t < 0.8f)
            {
                pos = m_JumpTargetPos;
                pos.y -= 20.0f * (t - 0.6f);
            }
            else
            {
                pos = m_JumpTargetPos;
                pos.y = m_JumpStartY;

                m_IsAttacking = false;
                m_CurrentAttack = AttackType::None;
            }

            m_Transform->SetPosition(pos);
            break;
        }

        case AttackType::DashCombo:
        {
            glm::vec3 pos = m_Transform->GetPosition();

            switch (m_ComboState)
            {
            case ComboState::Positioning:
            {
                glm::vec3 target = m_PlayerRef->GetComponent<Termina::Transform>().GetPosition();
                glm::vec3 dir = target - pos;
                dir.y = 0.0f;

                float dist = glm::length(dir);

                if (dist > m_MeleeAttackRange * 1.5f)
                {
                    pos += glm::normalize(dir) * m_Speed * deltaTime;
                }
                else
                {
                    glm::vec3 side = glm::cross(dir, glm::vec3(0, 1, 0));
                    if (rand() % 2) side = -side;

                    m_DashDir = glm::normalize(side);

                    m_ComboState = ComboState::Dash;
                    m_ComboTimer = 0.25f;
                }
                break;
            }

            case ComboState::Dash:
                pos += m_DashDir * 10.0f * deltaTime;

                m_ComboTimer -= deltaTime;
                if (m_ComboTimer <= 0.0f)
                    m_ComboState = ComboState::Check;
                break;

            case ComboState::Check:
                m_ComboStep++;

                if (m_ComboStep >= 3)
                {
                    m_ComboState = ComboState::Recovery;
                    m_ComboTimer = 0.5f;
                }
                else
                {
                    m_DashDir = -m_DashDir;
                    m_ComboState = ComboState::Dash;
                    m_ComboTimer = 0.35f;
                }
                break;

            case ComboState::Recovery:
                m_ComboTimer -= deltaTime;

                if (m_ComboTimer <= 0.0f)
                {
                    m_IsAttacking = false;
                    m_CurrentAttack = AttackType::None;
                    m_ComboState = ComboState::Positioning;
                    m_ComboStep = 0;
                }
                break;
            }

            m_Transform->SetPosition(pos);
            break;
        }
        }

        return;
    }

    // -------- TIMER --------
    m_AttackTimer -= deltaTime;

    if (m_InTransition)
    {
        m_PhaseTransitionTimer -= deltaTime;
        if (m_PhaseTransitionTimer <= 0.0f)
            m_InTransition = false;
        return;
    }

    // -------- PHASE --------
    float hpPercent = m_Health / m_MaxHealth;

    if (m_CurrentPhase == Phase::Phase1 && hpPercent <= 0.5f)
        EnterPhase(Phase::Phase2);

    if (m_CurrentPhase == Phase::Phase2 && hpPercent <= 0.1f)
    {
        EnterPhase(Phase::Phase3);
        m_MaxHealth = 125.0f;
        m_Health = 125.0f;
        m_UseMelee = false;
    }

    if (m_CurrentPhase == Phase::Phase3 && hpPercent <= 0.5f)
        EnterPhase(Phase::Phase4);

    // -------- POSITION --------
    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_PlayerRef->GetComponent<Termina::Transform>().GetPosition();
    glm::vec3 dir = target - pos;
    dir.y = 0.0f;

    float dist = glm::length(dir);
    float distSq = glm::dot(dir, dir);

    // -------- ATTACK DECISION (WITH WEIGHTS) --------
    if (!m_IsAttacking && m_AttackTimer <= 0.0f && m_NextAttack == AttackType::None)
    {
        float r = (float)(rand() % 100);

        float meleeW = 0.0f;
        float jumpW = 0.0f;
        float comboW = 0.0f;

        // -------- PHASE WEIGHTS --------
        if (m_CurrentPhase == Phase::Phase1)
        {
            meleeW = 40.0f;
            jumpW = 30.0f;
            comboW = 30.0f;
        }
        else if (m_CurrentPhase == Phase::Phase2)
        {
            meleeW = 40.0f;
            jumpW = 30.0f;
            comboW = 30.0f;
        }
        else if (m_CurrentPhase == Phase::Phase3)
        {
            meleeW = 40.0f;
            jumpW = 30.0f;
            comboW = 30.0f;
        }
        else // Phase 4
        {
            meleeW = 40.0f;
            jumpW = 30.0f;
            comboW = 30.0f;
        }

        if (r < meleeW)
            m_NextAttack = AttackType::MeleeBasic;
        else if (r < meleeW + jumpW)
            m_NextAttack = AttackType::Jump;
        else
            m_NextAttack = AttackType::DashCombo;
    }

    // -------- MOVE --------
    float targetDist = 0.0f;

    if (m_NextAttack != AttackType::None)
    {
        switch (m_NextAttack)
        {
        case AttackType::MeleeBasic:
            targetDist = m_MeleeAttackRange * 0.85f;
            break;

        case AttackType::Jump:
            targetDist = m_PrepareRange + 0.5f;
            break;

        case AttackType::DashCombo:
            targetDist = m_PrepareRange + 0.8f;
            break;
        }
    }
    else
    {
        switch (m_CurrentPhase)
        {
        case Phase::Phase1:
            targetDist = m_MeleeAttackRange * 0.8f;
            break;

        case Phase::Phase2:
        case Phase::Phase4:
            targetDist = m_UseMelee ? m_MeleeAttackRange * 0.8f : m_RangedAttackRange * 0.8f;
            break;

        case Phase::Phase3:
            targetDist = m_RangedAttackRange * 0.8f;
            break;
        }
    }

    float tolerance = 0.15f * targetDist;

    if (dist > 0.001f)
    {
        glm::vec3 moveDir = glm::normalize(dir);

        float error = dist - targetDist;

        float deadZone = 0.1f * targetDist;

        float speed = m_Speed;

        if (fabs(error) > deadZone)
        {
            float dirSign = (error > 0.0f) ? 1.0f : -1.0f;
            float slowFactor = glm::clamp(fabs(error) / targetDist, 0.2f, 1.0f);

            pos += moveDir * speed * slowFactor * deltaTime * dirSign;
        }
        else
        {
            pos += moveDir * error * 2.0f * deltaTime;
        }
    }

    // -------- ATTACK TRIGGER --------
    if (!m_IsAttacking && m_NextAttack != AttackType::None)
    {
        bool ready = false;

        switch (m_NextAttack)
        {
        case AttackType::MeleeBasic:
            ready = dist <= m_MeleeAttackRange;
            break;

        case AttackType::Jump:
            ready = dist >= m_PrepareRange &&
                dist <= m_RangedAttackRange;
            break;

        case AttackType::DashCombo:
            ready = dist >= m_PrepareRange &&
                dist <= m_RangedAttackRange * 1.3f;
            break;
        }

        if (ready)
        {
            m_CurrentAttack = m_NextAttack;
            m_NextAttack = AttackType::None;

            m_IsAttacking = true;
            m_AttackLocalTimer = 0.0f;

            if (m_CurrentAttack == AttackType::MeleeBasic)
                DoMeleeAttack();
            else if (m_CurrentAttack == AttackType::Jump)
            {
                glm::vec3 playerPos = m_PlayerRef->GetComponent<Termina::Transform>().GetPosition();

                glm::vec3 dir = playerPos - pos;
                dir.y = 0.0f;

                if (glm::length(dir) > 0.001f)
                    dir = glm::normalize(dir);

                m_JumpTargetPos = playerPos + dir * 0.5f;

                m_JumpStartY = pos.y;
            }
            else if (m_CurrentAttack == AttackType::DashCombo)
            {
                m_ComboState = ComboState::Positioning;
                m_ComboStep = 0;
            }

            m_AttackTimer = 2.0f;
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
    ImGui::DragFloat("Health", &m_Health, 100.0f, 0.0f, 10000.0f);
    ImGui::DragFloat("Max Health", &m_MaxHealth, 100.0f, 1.0f, 10000.0f);
    ImGui::DragFloat("Speed", &m_Speed, 2.f, 0.0f, 100.0f);
    ImGui::DragFloat("Melee Range", &m_MeleeAttackRange, 1.5f, 0.1f, 100.0f);
    ImGui::DragFloat("Ranged Range", &m_RangedAttackRange, 4.0f, 0.1f, 100.0f);
    ImGui::Text("Phase: %d", (int)m_CurrentPhase);
    ImGui::Text("State: %d", (int)m_CurrentAction);
    ImGui::Text("HP: %.1f / %.1f", m_Health, m_MaxHealth);
    ImGui::Text("Next Attack: %d", (int)m_NextAttack);
    ImGui::Text("Current Attack: %d", (int)m_CurrentAttack);
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

void BossScript::EnterPhase(Phase newPhase)
{
    m_CurrentPhase = newPhase;
    m_InTransition = true;
    m_PhaseTransitionTimer = 2.0f;

    m_AttackTimer = 0.0f;
    m_AttackSwitchTimer = m_AttackSwitchCooldown;
    m_CurrentAction = State::Idle;
}

void BossScript::DoMeleeAttack()
{
    TN_INFO("Boss: Melee Attack");

    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_PlayerRef->GetComponent<Termina::Transform>().GetPosition();

    m_MeleeDir = target - pos;
    m_MeleeDir.y = 0.0f;

    if (glm::length(m_MeleeDir) > 0.001f)
        m_MeleeDir = glm::normalize(m_MeleeDir);

    m_MeleeState = MeleeState::Forward;
    m_MeleeTimer = m_MeleeForwardDuration;
}

void BossScript::DoRangedAttack()
{
    TN_INFO("Boss: Ranged Attack");

    // TODO:
    // - spawn projectile
    // - viser le joueur
}

void BossScript::Die()
{
    if (m_IsDead)
        return;

    m_IsDead = true;
    m_DeathTimer = m_DeathDuration;

    TN_INFO("Boss: Dead");

    // TODO:
    // - déclencher event victoire
}

void BossScript::TakeDamage(float amount)
{
    if (m_IsDead)
        return;

    m_Health -= amount;

    TN_INFO("Boss took damage: %.1f (HP: %.1f)", amount, m_Health);
}

// Le player ne bouge toujours pas
// Il se tp avant de jump sans raison
// Il ne fait pas de preparation bien visible du jump pour prevoir
// Le dash c'est n'imp