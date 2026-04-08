#include "PlayerComponent.hpp"
#include "GameManagerComponent.hpp"
#include "EnnemyComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <Termina/World/World.hpp>
#include <glm/glm.hpp>

void PlayerComponent::Start()
{
    health = 100.0f;
    isDead = false;
}

void PlayerComponent::Update(float deltaTime)
{
    // === BLOQUE SI GAME OVER ===
    if (GameManagerComponent::Instance && GameManagerComponent::Instance->IsGameOver())
        return;

    // === PERTE DE VIE AVEC O ===
    if (Input::IsKeyPressed(Termina::Key::O))
    {
        health -= 10.0f;
        TN_INFO("HP = %f", health);
    }

    // === TIR AVEC CLIC GAUCHE ===
    if (Input::IsMouseButtonPressed(Termina::MouseButton::Left))
    {
        auto* world = m_Owner->GetParentWorld();
        if (!world) return;
        OnColl
        glm::vec3 playerPos = m_Transform->GetPosition();
        glm::vec3 forward = m_Transform->GetForward();

        for (auto& actorPtr : world->GetActors())
        {
            Termina::Actor* actor = actorPtr.get();
            if (actor->HasComponent<EnnemyComponent>())
            {
                auto& enemy = actor->GetComponent<EnnemyComponent>();
                if (enemy.IsHitByRay(playerPos, forward))
                {
                    enemy.TakeDamage(10); // dégâts du clic gauche
                    TN_INFO("Enemy hit by player!");
                }
            }
        }
    }

    // === MORT DU JOUEUR ===
    if (!isDead && health <= 0.0f)
    {
        isDead = true;
        TN_INFO("Player died!");
        if (GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerLose();
    }
}