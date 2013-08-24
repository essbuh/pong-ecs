//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "InputSystem.h"

#include <coment/World.h>

#include "Components/ControlComponent.h"
#include "Components/KeyBindingComponent.h"

//-----------------------------------------------------------------------------
void InputSystem::registerComponents( void )
{
	registerComponent<ControlComponent>();
	registerComponent<KeyBindingComponent>();
}

//-----------------------------------------------------------------------------
void InputSystem::process(const coment::Entity& e)
{
	ControlComponent *control = _world->getComponent<ControlComponent>(e);
	KeyBindingComponent *keyBinding = _world->getComponent<KeyBindingComponent>(e);

	control->up = (keyBinding->upKey > 0) && _keyState[keyBinding->upKey];
	control->down = (keyBinding->downKey > 0) && _keyState[keyBinding->downKey];
}