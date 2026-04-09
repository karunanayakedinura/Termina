#include "MeleeEnnemyComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <glm/glm.hpp>

void MeleeEnnemyComponent::Attack(float deltaTime)
{
    if (!m_Player)
        return;

    float dist = glm::distance(
        m_Transform->GetPosition(),
        m_Player->GetComponent<Termina::Transform>().GetPosition()
    );

    // Distance d'attaque corps à corps
    if (dist < 1.5f)
    {
        TN_INFO("Melee enemy hits player for %d damage!", m_Damage);

        // TODO : appeler Player->TakeDamage(m_Damage)
    }
}
