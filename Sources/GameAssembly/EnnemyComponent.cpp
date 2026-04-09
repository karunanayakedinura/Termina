#include "EnnemyComponent.hpp"
#include "PlayerComponent.hpp"
#include "GameManagerComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void EnnemyComponent::Start()
{
    TN_INFO("Enemy spawned with %d HP", m_Health);
}

void EnnemyComponent::Update(float deltaTime)
{
    if (m_Health <= 0 && GameManagerComponent::Instance)
    {
        GameManagerComponent::Instance->TriggerWin();
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

