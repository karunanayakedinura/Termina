#include "ThirdPersonCam.hpp"

void GameComponent::ThirdPersonCameraComponent::Start(){}

void GameComponent::ThirdPersonCameraComponent::Update(float deltaTime) {
    if (!m_TargetActor) return;

    Termina::Transform& targetTransform = m_TargetActor->GetComponent<Termina::Transform>();
    Termina::Transform& cameraTransform = GetOwner()->GetComponent<Termina::Transform>();

    // Calculate desired position behind player
    glm::vec3 targetPos = targetTransform.GetPosition()
        - targetTransform.GetForward() * m_Distance
        + glm::vec3(0, m_Height, 0);

    // Smoothly interpolate camera position
    glm::vec3 desiredPos = glm::mix(
        cameraTransform.GetPosition(),
        targetPos,
        m_SmoothSpeed
    );

    cameraTransform.SetPosition(desiredPos);

    // Look at player
    glm::vec3 direction = glm::normalize(
        targetTransform.GetPosition() - desiredPos + glm::vec3(0, 0.5f, 0)
    );
    cameraTransform.LookAt(direction);
    }