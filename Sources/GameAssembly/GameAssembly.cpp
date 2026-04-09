#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"
#include "PlayerComponent.hpp"
#include "BossScript.hpp"
#include "EnnemySpawner.hpp"
#include "MeleeEnnemyComponent.hpp"
#include "RangedEnnemyComponent.hpp"
#include "MainMenuComponent.hpp"

COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")
    REGISTER_COMPONENT(PlayerComponent, "Player Component")
    REGISTER_COMPONENT(BossScript, "Boss Script")
    REGISTER_COMPONENT(EnnemySpawner, "Ennemy Spawner")
    REGISTER_COMPONENT(MeleeEnnemyComponent, "Melee Ennemy Component")
    REGISTER_COMPONENT(RangedEnnemyComponent, "Ranged Ennemy Component")
    REGISTER_COMPONENT(MainMenuComponent, "Main Menu Component")
COMPONENT_MODULE_END()
