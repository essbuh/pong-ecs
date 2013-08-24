//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _BALLMANAGER_H_ )
#define _BALLMANAGER_H_

#include "coment/managers/Manager.h"
#include "coment/World.h"

#include "Components/PositionComponent.h"
#include "Components/BoundsComponent.h"
#include "Components/ColorComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PreviousUpdatePositionComponent.h"

//-----------------------------------------------------------------------------
static int MAX_BALL_VELOCITY = 300;
static int MIN_BALL_VELOCITY = -300;

//-----------------------------------------------------------------------------
class BallManager : public coment::Manager
{
public:
	void createBall( void )
	{
		coment::Entity e = _world->createEntity();
		_world->addGroup(e, "balls");

		int width = _world->getValue<int>("window_width");
		int height = _world->getValue<int>("window_height");

		PositionComponent *position = _world->addComponent<PositionComponent>(e);
		position->x = width / 2.f;
		position->y = height / 2.f;

		PreviousUpdatePositionComponent *lastPosition = _world->addComponent<PreviousUpdatePositionComponent>(e);
		lastPosition->x = position->x;
		lastPosition->y = position->y;

		BoundsComponent *bounds = _world->addComponent<BoundsComponent>(e);
		bounds->width = 50.f;
		bounds->height = 50.f;

		ColorComponent *color = _world->addComponent<ColorComponent>(e);
		color->r = rand() % 255;
		color->g = rand() % 255;
		color->b = rand() % 255;

		VelocityComponent *velocity = _world->addComponent<VelocityComponent>(e);
		do 
		{
			velocity->x = rand() % (MAX_BALL_VELOCITY - MIN_BALL_VELOCITY) + MIN_BALL_VELOCITY;
			velocity->y = rand() % (MAX_BALL_VELOCITY - MIN_BALL_VELOCITY) + MIN_BALL_VELOCITY;
		} while (velocity->x == 0 || velocity->y == 0);
	}
};

#endif // _BALLMANAGER_H_