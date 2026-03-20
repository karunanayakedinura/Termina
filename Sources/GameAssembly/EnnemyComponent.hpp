#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class EnnemyComponent : public ScriptableComponent
{
public:
    EnnemyComponent() = default;
    EnnemyComponent(Termina::Actor* owner) : ScriptableComponent(owner) {}

    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void OnCollisionEnter(Termina::Actor* other) override;

    void Inspect() override;
    void Serialize(nlohmann::json& out) const override;
    void Deserialize(const nlohmann::json& in) override;

private:
    float m_Speed = 2.0f;
    int   m_Health = 10;
    int   m_Damage = 10;

    Termina::Actor* m_Player = nullptr;
};

