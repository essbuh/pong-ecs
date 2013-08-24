//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "MovementSystem.h"

#include <coment/World.h>

#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"

//-----------------------------------------------------------------------------
void MovementSystem::registerComponents( void )
{
	registerComponent<PositionComponent>();
	registerComponent<VelocityComponent>();
}

//-----------------------------------------------------------------------------
void MovementSystem::process(const coment::Entity& e)
{
	PositionComponent *position = _world->getComponent<PositionComponent>(e);
	VelocityComponent *velocity = _world->getComponent<VelocityComponent>(e);

	float dt = _world->getDelta();

	position->x += velocity->x * dt;
	position->y += velocity->y * dt;
}