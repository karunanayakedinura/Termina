#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

namespace GameComponent {
    class WeaponSpawner : public TerminaScript::ScriptableComponent {
    public:
        WeaponSpawner() = default;
        WeaponSpawner(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}

        void Start() override;
        void Update(float deltaTime) override;

        void Inspect() override;
        void Serialize(nlohmann::json& out) const override;
        void Deserialize(const nlohmann::json& in) override;

    private:
        float m_Time;
        float m_Timer;

        TerminaScript::Prefab m_Gun;
    };
}