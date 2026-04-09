#pragma once
#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

namespace GameComponent {

    class ThirdPersonCameraComponent : public TerminaScript::ScriptableComponent{
    private:
        Termina::Actor* m_TargetActor = nullptr;
        float m_Distance = 5.0f;
        float m_Height = 2.0f;
        float m_SmoothSpeed = 0.1f;
        glm::vec3 m_CurrentOffset;

    public:
        void Start() override;
        void Update(float deltaTime) override;

        ThirdPersonCameraComponent() = default;
        ThirdPersonCameraComponent(Termina::Actor* owner) : TerminaScript::ScriptableComponent(owner) {}
    };
}