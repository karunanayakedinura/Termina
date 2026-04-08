#include "GameManagerComponent.hpp"

GameManagerComponent* GameManagerComponent::Instance = nullptr;


GameManagerComponent::GameManagerComponent()
{
    Instance = this;
}

GameManagerComponent::GameManagerComponent(Termina::Actor* owner)
    : ScriptableComponent(owner)
{
    Instance = this;
}

void GameManagerComponent::Update(float dt)
{
    // rien pour l'instant
}

void GameManagerComponent::TriggerWin()
{
    m_GameOver = true;
    m_Win = true;
}

void GameManagerComponent::TriggerLose()
{
    m_GameOver = true;
    m_Win = false;
}

void GameManagerComponent::Stop()
{
    Instance = nullptr;
}