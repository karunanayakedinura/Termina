#include "ProjectileComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>
#include "MeleeEnnemyComponent.hpp"

void GameComponent::ProjectileComponent::Start() {}

void GameComponent::ProjectileComponent::Stop() {
	Destroy(m_Owner);
}

void GameComponent::ProjectileComponent::Update(float deltaTime) {
	glm::vec3 pos = m_Transform->GetPosition() + glm::vec3(0.f, 0.f, -m_Speed) * deltaTime;
 	m_Transform->SetPosition(pos);


	///////////// CRASH /////////////////
	/*if (m_Transform->GetPosition().z < -170) {
		Destroy(m_Owner);
	}*/
}

void GameComponent::ProjectileComponent::OnTriggerEnter(Termina::Actor* other) {
	if (other->HasComponent(MeleeEnnemyComponent)) {
		other->TakeDamage(10);
	}
}
