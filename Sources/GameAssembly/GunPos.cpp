#include "GunPos.hpp"

void GunPos::Start() {

	m_Player = m_Owner->GetParentWorld()->GetActorByName("Player");

	if (!m_Player)
		TN_WARN("Enemy: Player not found in scene!");
	
}

void GunPos::Update(float dt) {
	if (m_Owner->GetComponent<Termina::Transform>().GetPosition() != m_Player->GetComponent<Termina::Transform>().GetPosition())
		m_Owner->GetComponent<Termina::Transform>().SetPosition(glm::vec3(
			  m_Player->GetComponent<Termina::Transform>().GetPosition().x
			, m_Player->GetComponent<Termina::Transform>().GetPosition().y +2
			, m_Player->GetComponent<Termina::Transform>().GetPosition().z +1));

}

