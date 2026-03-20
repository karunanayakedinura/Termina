#include "EnnemySpawner.hpp"
#include <ImGui/imgui.h>
#include <Termina/Core/Logger.hpp>

void EnnemySpawner::Start()
{
    m_Timer = 0.0f;
}

void EnnemySpawner::Update(float deltaTime)
{
    if (m_SpawnOnce && m_HasSpawned)
        return;

    m_Timer += deltaTime;

    if (m_Timer >= m_SpawnDelay)
    {
        m_Timer = 0.0f;

        // Spawn de l'ennemi
        Termina::Actor* enemy = Instantiate(m_EnemyPrefab);

        if (enemy)
            TN_INFO("Enemy spawned!");

        m_HasSpawned = true;
    }
}

void EnnemySpawner::Inspect()
{
    ImGui::DragFloat("Spawn Delay", &m_SpawnDelay, 0.1f, 0.1f, 60.0f);
    ImGui::Checkbox("Spawn Once", &m_SpawnOnce);
    m_EnemyPrefab.Inspect("Enemy Prefab");
}
