#include "RangedEnnemyComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <glm/glm.hpp>

void RangedEnnemyComponent::Attack(float deltaTime)
{
    if (!m_Player)
        return;

    m_Timer -= deltaTime;

    if (m_Timer <= 0.0f)
    {
        m_Timer = m_ShootCooldown;

        TN_INFO("Ranged enemy shoots projectile! Damage = %d", m_Damage);

        // TODO :
        // Termina::Actor* proj = Instantiate(projectilePrefab);
        // proj->GetComponent<Transform>().SetPosition(m_Transform->GetPosition());
        // proj->GetComponent<Rigidbody>().AddForce(direction * force);
    }
}
