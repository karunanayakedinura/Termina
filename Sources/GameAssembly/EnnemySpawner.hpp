#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class EnnemySpawner : public ScriptableComponent
{
public:
    EnnemySpawner() = default;
    EnnemySpawner(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void Start() override;
    void Update(float deltaTime) override;
    void Inspect() override;

private:
    float m_SpawnDelay = 3.0f;     // Temps avant spawn
    float m_Timer = 0.0f;          // Compteur interne
    Prefab m_EnemyPrefab;          // Le prefab de ton ennemi
    bool m_SpawnOnce = true;       // Spawn unique ou repetitif
    bool m_HasSpawned = false;
};
