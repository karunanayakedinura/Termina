#include "ProjectileComponent.hpp"
#include <Termina/Core/Logger.hpp>

void ProjectileComponent::Start() {}

void ProjectileComponent::Stop() {
	Destroy(m_Owner);
}

void ProjectileComponent::Update(float deltaTime) {
	glm::vec3 pos = m_Transform->GetPosition() + glm::vec3(0.f, 0.f, m_Speed);
 	m_Transform->SetPosition(pos);

	/*if (m_Transform->GetPosition() < ? || collision) {
		Destroy(m_Owner);
	}*/
}