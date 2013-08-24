//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "ControlMovementSystem.h"

#include <coment/World.h>

#include "Components/ControlComponent.h"
#include "Components/VelocityComponent.h"

//-----------------------------------------------------------------------------
const float PADDLE_SPEED = 450.f;

//-----------------------------------------------------------------------------
void ControlMovementSystem::registerComponents( void )
{
	registerComponent<ControlComponent>();
	registerComponent<VelocityComponent>();
}

//-----------------------------------------------------------------------------
void ControlMovementSystem::process(const coment::Entity& e)
{
	ControlComponent *control = _world->getComponent<ControlComponent>(e);
	VelocityComponent *velocity = _world->getComponent<VelocityComponent>(e);

	velocity->y = control->up * PADDLE_SPEED + control->down * -PADDLE_SPEED;
}