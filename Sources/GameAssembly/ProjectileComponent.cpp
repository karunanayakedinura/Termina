#include "ProjectileComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void GameComponent::ProjectileComponent::Start() {}

void GameComponent::ProjectileComponent::Stop() {
	m_Enemy = nullptr;
	m_MeleeEnemy = nullptr;
	m_RangedEnemy = nullptr;

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
	if (other->HasComponent<MeleeEnnemyComponent>() || other->HasComponent<RangedEnnemyComponent>() || other->HasComponent<EnnemyComponent>()) {
		other->GetComponent<MeleeEnnemyComponent>().TakeDamage(20);
	}
}
