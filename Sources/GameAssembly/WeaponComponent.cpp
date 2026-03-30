#include "WeaponComponent.hpp"
#include <Termina/Core/Logger.hpp>
#include <ImGui/imgui.h>

void WeaponComponent::Start(){}

void WeaponComponent::Update(float deltaTime) {
	//if (Input::IsKeyHeld(Termina::Key::E) && /*Player in collision*/) {      IDK CHANGEMENT D'ARME

	//}
}

void WeaponComponent::MunitionSpawner(){
	Termina::Actor* bullet = Instantiate();
	// bullet->GetComponent<Termina::Transform>().SetPosition();
}