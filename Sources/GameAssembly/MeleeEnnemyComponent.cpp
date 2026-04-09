#include "MeleeEnnemyComponent.hpp"
#include "GameManagerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <glm/glm.hpp>

void MeleeEnnemyComponent::Start()
{
    auto* world = m_Owner->GetParentWorld();
    if (world)
        m_Player = world->GetActorByName("Player");
}

void MeleeEnnemyComponent::Update(float deltaTime)
{
    // === PERTE DE VIE AVEC P ===
    if (Input::IsKeyPressed(Termina::Key::P))
    {
        m_Health -= 10.0f;
        TN_INFO("Enemy HP = %f", m_Health);
    }
    if (m_Health <= 0)
    {
        if (GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerWin();
        return;
    }

    if (!m_Player)
        return;

    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_Player->GetComponent<Termina::Transform>().GetPosition();

    glm::vec3 dir = target - pos;
    dir.y = 0.0f;

    float dist = glm::length(dir);
    if (dist < 0.001f)
        return;

    dir = glm::normalize(dir);

    // --- Rotation vers le joueur (radians + offset) ---
    float yaw = atan2(dir.x, dir.z);
    yaw += glm::radians(180.0f); // <-- CORRECTION ICI

    m_Transform->SetRotation(glm::vec3(0.0f, yaw, 0.0f));

    // --- Déplacement ou attaque ---
    if (dist > m_AttackRange)
    {
        pos += dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    else
    {
        //TN_INFO("Melee enemy hits player for %f damage!", m_Damage);
    }
}

void MeleeEnnemyComponent::OnCollisionEnter(Termina::Actor* other)
{
    TN_INFO("MeleeEnnemy OnCollisionEnter with {}", other ? other->GetName().c_str() : "null");

    if (!other)
        return;

    if (other->GetName() == "Player")
    {
        m_Health -= 10; 
        TN_INFO("Melee enemy took 10 damage, HP = %d", m_Health);

        if (m_Health <= 0 && GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerWin();
    }
}

void MeleeEnnemyComponent::TakeDamage(float value)
{
    m_Health -= value;
    TN_INFO("Melee enemy took %f damage, HP = %f", value, m_Health);

    if (m_Health <= 0)
    {
        if (GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerWin();
    }
}







