//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "PositionStorageSystem.h"

#include <coment/World.h>

#include "Components/PositionComponent.h"
#include "Components/PreviousUpdatePositionComponent.h"

//-----------------------------------------------------------------------------
void PositionStorageSystem::registerComponents( void )
{
	registerComponent<PositionComponent>();
	registerComponent<PreviousUpdatePositionComponent>();
}

//-----------------------------------------------------------------------------
void PositionStorageSystem::process(const coment::Entity& e)
{
	PositionComponent *position = _world->getComponent<PositionComponent>(e);
	PreviousUpdatePositionComponent *lastPosition = _world->getComponent<PreviousUpdatePositionComponent>(e);

	lastPosition->x = position->x;
	lastPosition->y = position->y;
}