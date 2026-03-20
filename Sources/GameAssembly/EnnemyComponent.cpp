#include "EnnemyComponent.hpp"
#include <ImGui/imgui.h>
#include <Termina/Core/Logger.hpp>

void EnnemyComponent::Awake()
{
    // Initialisation tres tot (avant Start)
}

void EnnemyComponent::Start()
{
    TN_INFO("Enemy spawned with %d HP", GetHealth());

    // Recupere l'acteur nomme "Player"
    m_Player = m_Owner->GetParentWorld()->GetActorByName("Player");

    if (!m_Player)
        TN_WARN("Enemy: Player not found in scene!");
}

void EnnemyComponent::Update(float deltaTime)
{
    if (!m_Player)
        return;

    // Position de l'ennemi
    glm::vec3 pos = m_Transform->GetPosition();

    // Position du joueur
    glm::vec3 target = m_Player->GetComponent<Termina::Transform>().GetPosition();

    // Direction vers le joueur
    glm::vec3 dir = target - pos;

    // On ignore la hauteur
    dir.y = 0.0f;

    // Normalisation
    dir = glm::normalize(dir);

    // --- ROTATION AUTOMATIQUE ---
    glm::quat rot = glm::quatLookAt(dir, glm::vec3(0, 1, 0));
    m_Transform->SetRotation(rot);

    // --- DEPLACEMENT ---
    pos += dir * m_Speed * deltaTime;
    m_Transform->SetPosition(pos);
}

void EnnemyComponent::OnCollisionEnter(Termina::Actor* other)
{
    TN_INFO("Enemy collided with %s (HP = %d)",
        other->GetName().c_str(),
        GetHealth());
}

void EnnemyComponent::Inspect()
{
    ImGui::DragFloat("Speed", &m_Speed, 0.1f);
    ImGui::DragInt("Health", &m_Health, 1, 0, 100);
    ImGui::DragInt("Damage", &m_Damage, 1, 0, 100);
}

void EnnemyComponent::Serialize(nlohmann::json& out) const
{
    out["speed"] = m_Speed;
    out["health"] = m_Health;
    out["damage"] = m_Damage;
}

void EnnemyComponent::Deserialize(const nlohmann::json& in)
{
    if (in.contains("speed"))  m_Speed = in["speed"];
    if (in.contains("health")) m_Health = in["health"];
    if (in.contains("damage")) m_Damage = in["damage"];
}
