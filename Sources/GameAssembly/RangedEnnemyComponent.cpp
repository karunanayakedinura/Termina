#include "RangedEnnemyComponent.hpp"
#include "GameManagerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <glm/glm.hpp>

void RangedEnnemyComponent::Start()
{
    auto* world = m_Owner->GetParentWorld();
    if (world)
        m_Player = world->GetActorByName("Player");
}

void RangedEnnemyComponent::Update(float deltaTime)
{
    if (m_Health <= 0)
    {
        TN_INFO("Enemy died!");

        m_Health = 0;

        SetActive(false);

        m_Transform->SetPosition(glm::vec3(0.0f, -1000.0f, 0.0f));

        m_Transform->SetRotation(glm::vec3(0.0f));

        ///if (GameManagerComponent::Instance)
            ///GameManagerComponent::Instance->TriggerWin();
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
    yaw += glm::radians(-90.0f); 

    m_Transform->SetRotation(glm::vec3(0.0f, yaw, 0.0f));

    // --- Fuite si trop proche ---
    if (dist <= m_MinDistance)
    {
        pos -= dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    // --- Poursuite si trop loin ---
    else if (dist >= m_MaxDistance)
    {
        pos += dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    // --- Zone de tir ---
    else
    {
        m_Timer += deltaTime;

        if (m_Timer >= m_ShootCooldown)
        {
            m_Timer = 0.0f;
            TN_INFO("Ranged enemy shoots player for %f damage!", m_Damage);
        }
    }
}

void RangedEnnemyComponent::OnTriggerEnter(Termina::Actor* other)
{
    TN_INFO("RangedEnnemy OnCollisionEnter with {}", other ? other->GetName().c_str() : "null");


    if (!other)
        return;

    if (other->GetName() == "Player")
    {
        m_Health -= 10;
        TN_INFO("Ranged enemy took 10 damage, HP = %d", m_Health);

        ///if (m_Health <= 0 && GameManagerComponent::Instance)
            ///GameManagerComponent::Instance->TriggerWin();
    }
}

void RangedEnnemyComponent::TakeDamage(float value)
{
    m_Health -= value;
    TN_INFO("Ranged enemy took %f damage, HP = %d", value, m_Health);

    if (m_Health <= 0)
    {
        TN_INFO("Enemy died!");

        auto* world = m_Owner->GetParentWorld();
        if (world)
            world->DestroyActor(m_Owner);

        ///if (GameManagerComponent::Instance)
            ///GameManagerComponent::Instance->TriggerWin();
    }
}







