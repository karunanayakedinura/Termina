#include "ProjectileComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void ProjectileComponent::Start() {}

void ProjectileComponent::Stop() {
	Destroy(m_Owner);
}

void ProjectileComponent::Update(float deltaTime) {
	glm::vec3 pos = m_Transform->GetPosition() + glm::vec3(0.f, 0.f, -m_Speed) * deltaTime;
 	m_Transform->SetPosition(pos);

	/*if (m_Transform->GetPosition().z < 300 || collision) {
		Destroy(m_Owner);
	}*/
}

void ProjectileComponent::Inspect(){
	ImGui::DragFloat("Speed", &m_Speed, 0.5f);
}