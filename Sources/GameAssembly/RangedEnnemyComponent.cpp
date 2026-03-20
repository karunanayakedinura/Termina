#include "RangedEnnemyComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>
#include <glm/glm.hpp>

void RangedEnnemyComponent::Attack(float deltaTime)
{
    if (!m_Player)
        return;

    glm::vec3 pos = m_Transform->GetPosition();
    glm::vec3 target = m_Player->GetComponent<Termina::Transform>().GetPosition();

    glm::vec3 dir = target - pos;
    dir.y = 0.0f;

    float dist = glm::length(dir);

    if (dist > 0.01f)
        dir = glm::normalize(dir);

    // --- LOGIQUE DE DISTANCE ---
    if (dist < m_MinDistance)
    {
   
        pos -= dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    else if (dist > m_MaxDistance)
    {
    
        pos += dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    else
    {
      
        m_Timer -= deltaTime;

        if (m_Timer <= 0.0f)
        {
            m_Timer = m_ShootCooldown;

            TN_INFO("Ranged enemy shoots projectile! Damage = %d", m_Damage);

            // TODO : spawn projectile
        }
    }
}

void RangedEnnemyComponent::Inspect()
{
    // Inspect de la classe de base
    EnnemyComponent::Inspect();

    // Paramètres specifiques au ranged
    ImGui::Separator();
    ImGui::Text("Ranged Settings");

    ImGui::DragFloat("Min Distance", &m_MinDistance, 0.1f, 0.0f, 50.0f);
    ImGui::DragFloat("Max Distance", &m_MaxDistance, 0.1f, 0.0f, 50.0f);

    ImGui::DragFloat("Shoot Cooldown", &m_ShootCooldown, 0.1f, 0.1f, 10.0f);
}
