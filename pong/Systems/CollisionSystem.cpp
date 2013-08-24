//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "CollisionSystem.h"

#include <coment/World.h>

#include "Components/PositionComponent.h"
#include "Components/BoundsComponent.h"
#include "Components/VelocityComponent.h"

//-----------------------------------------------------------------------------
void CollisionSystem::registerComponents( void )
{
	registerComponent<PositionComponent>();
	registerComponent<BoundsComponent>();
	registerComponent<VelocityComponent>();
}

//-----------------------------------------------------------------------------
void CollisionSystem::process(const coment::Entity& e)
{
	PositionComponent *position = _world->getComponent<PositionComponent>(e);
	BoundsComponent *bounds = _world->getComponent<BoundsComponent>(e);
	VelocityComponent *velocity = _world->getComponent<VelocityComponent>(e);

	int width = _world->getValue<int>("window_width");
	if (position->x < 0)
	{
		position->x = 0;
		velocity->x = -velocity->x;
	}
	else if ((position->x + bounds->width) >= width)
	{
		position->x = width - bounds->width;
		velocity->x = -velocity->x;
	}

	int height = _world->getValue<int>("window_height");
	if (position->y < 0)
	{
		position->y = 0;
		velocity->y = -velocity->y;
	}
	else if ((position->y + bounds->height) >= height)
	{
		position->y = height - bounds->height;
		velocity->y = -velocity->y;
	}
}