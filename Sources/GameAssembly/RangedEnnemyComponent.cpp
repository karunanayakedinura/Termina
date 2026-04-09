#include "RangedEnnemyComponent.hpp"
#include <Termina/Core/Logger.hpp>
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
    dir = glm::normalize(dir);

    // ---- LOGIQUE DE DISTANCE ----
    if (dist <= m_MinDistance)
    {
        pos -= dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    else if (dist >= m_MaxDistance)
    {
        pos += dir * m_Speed * deltaTime;
        m_Transform->SetPosition(pos);
    }
    else
    {
        m_Timer += deltaTime;

        if (m_Timer >= m_ShootCooldown)
        {
            m_Timer = 0.0f;
            TN_INFO("Ranged enemy shoots player!");
            // TODO: Player->TakeDamage(m_Damage);
        }
    }
}
