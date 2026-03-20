#include <Termina/Scripting/API/ScriptingAPI.hpp>
#include <Termina/World/ComponentRegistry.hpp>

#include "FlyCamComponent.hpp"
#include "ParticleSystem.hpp"
#include "PhysicsTestComponent.hpp"
#include "PlayerComponent.hpp"
#include "EnnemyComponent.hpp"
#include "EnnemySpawner.hpp"
#include "WeaponComponent.hpp"
#include "ProjectileComponent.hpp"

COMPONENT_MODULE_BEGIN()
    REGISTER_COMPONENT(FlyCamComponent, "Fly Cam Component")
    REGISTER_COMPONENT(ParticleSystemComponent, "Particle System")
    REGISTER_COMPONENT(PhysicsTestComponent, "Physics Test")
    REGISTER_COMPONENT(PlayerComponent, "Player Component")
    REGISTER_COMPONENT(EnnemyComponent, "Ennemy Component")
    REGISTER_COMPONENT(EnnemySpawner, "Ennemy Spawner")
    REGISTER_COMPONENT(WeaponComponent, "Weapon Component")
    REGISTER_COMPONENT(ProjectileComponent, "Projectile Component")
COMPONENT_MODULE_END()
