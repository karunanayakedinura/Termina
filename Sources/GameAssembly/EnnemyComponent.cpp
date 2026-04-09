#include "EnnemyComponent.hpp"
#include "PlayerComponent.hpp"
#include "GameManagerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void EnnemyComponent::Start()
{
    TN_INFO("Enemy spawned with %d HP", m_Health);

    // Cherche l'acteur nommé "Player"
    auto* world = m_Owner->GetParentWorld();
    if (world)
        m_Player = world->GetActorByName("Player");
}

void EnnemyComponent::Update(float deltaTime)
{
    if (m_Health <= 0 && GameManagerComponent::Instance)
    {
        GameManagerComponent::Instance->TriggerWin();
        return;
    }

    if (!m_Player)
        return;

    // --- Déplacement vers le joueur ---
    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_Player->GetComponent<Termina::Transform>().GetPosition();

    glm::vec3 dir = target - pos;
    dir.y = 0.0f; // pas de mouvement vertical

    float dist = glm::length(dir);
    if (dist > 0.1f) // évite les tremblements
    {
        dir = glm::normalize(dir);
        pos += dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
}

void EnnemyComponent::TakeDamage(int amount)
{
    m_Health -= amount;
    TN_INFO("Enemy took %d damage, HP = %d", amount, m_Health);

    if (m_Health <= 0 && GameManagerComponent::Instance)
    {
        GameManagerComponent::Instance->TriggerWin();
    }
}

