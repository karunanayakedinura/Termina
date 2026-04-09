#include "PlayerComponent.hpp"
#include "GameManagerComponent.hpp"
#include "MeleeEnnemyComponent.hpp"
#include "RangedEnnemyComponent.hpp"
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

    // === MORT DU JOUEUR ===
    if (!isDead && health <= 0.0f)
    {
        isDead = true;
        TN_INFO("Player died!");
        if (GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerLose();
    }
}

void PlayerComponent::OnTriggerEnter(Termina::Actor* other)
{
    TN_INFO("Player OnCollisionEnter with {}", other ? other->GetName().c_str() : "null");

    if (!other)
        return;

    if (Input::IsMouseButtonPressed(Termina::MouseButton::Left))
    {
        if (other->HasComponent<MeleeEnnemyComponent>())
        {
            other->GetComponent<MeleeEnnemyComponent>().TakeDamage(10);
        }

        if (other->HasComponent<RangedEnnemyComponent>())
        {
            other->GetComponent<RangedEnnemyComponent>().TakeDamage(10);
        }
    }
}

void PlayerComponent::TakeDamage(float value)
{
    health -= value;
    TN_INFO("Player took %f damage, HP = %f", value, health);

    if (!isDead && health <= 0.0f)
    {
        isDead = true;
        TN_INFO("Player died!");
        if (GameManagerComponent::Instance)
            GameManagerComponent::Instance->TriggerLose();
    }
}

