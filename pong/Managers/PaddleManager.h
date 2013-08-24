//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _PADDLEMANAGER_H_ )
#define _PADDLEMANAGER_H_

#include "coment/managers/Manager.h"
#include "coment/World.h"
#include <GLFW/glfw3.h>

#include "Components/PositionComponent.h"
#include "Components/BoundsComponent.h"
#include "Components/ColorComponent.h"
#include "Components/ControlComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PreviousUpdatePositionComponent.h"
#include "Components/KeyBindingComponent.h"

//-----------------------------------------------------------------------------
static float INITIAL_PADDLE_WIDTH = 20.f;
static float INITIAL_PADDLE_HEIGHT = 200.f;

//-----------------------------------------------------------------------------
class PaddleManager : public coment::Manager
{
public:
	void createPaddles( void )
	{
		int width = _world->getValue<int>("window_width");

		createPaddleAtPosition( 0, GLFW_KEY_W, GLFW_KEY_S, "PLAYER1" );
		createPaddleAtPosition( width - INITIAL_PADDLE_WIDTH, GLFW_KEY_UP, GLFW_KEY_DOWN, "PLAYER2" );
	}

	void createPaddleAtPosition( int xpos, int upKey, int downKey, std::string tag )
	{
		coment::Entity e = _world->createEntity();
		_world->addGroup(e, "paddles");
		_world->setTag(e, tag);

		int height = _world->getValue<int>("window_height");

		PositionComponent *position = _world->addComponent<PositionComponent>(e);
		position->x = xpos;
		position->y = height / 2.f;

		PreviousUpdatePositionComponent *lastPosition = _world->addComponent<PreviousUpdatePositionComponent>(e);
		lastPosition->x = position->x;
		lastPosition->y = position->y;

		BoundsComponent *bounds = _world->addComponent<BoundsComponent>(e);
		bounds->width = INITIAL_PADDLE_WIDTH;
		bounds->height = INITIAL_PADDLE_HEIGHT;

		ColorComponent *color = _world->addComponent<ColorComponent>(e);
		color->r = rand() % 255;
		color->g = rand() % 255;
		color->b = rand() % 255;

		VelocityComponent *velocity = _world->addComponent<VelocityComponent>(e);
		velocity->x = 0.f;
		velocity->y = 0.f;

		ControlComponent *control = _world->addComponent<ControlComponent>(e);

		KeyBindingComponent *keyBinds = _world->addComponent<KeyBindingComponent>(e);
		keyBinds->upKey = upKey;
		keyBinds->downKey = downKey;
	}
};

#endif // _PADDLEMANAGER_H_