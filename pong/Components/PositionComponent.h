//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _POSITIONCOMPONENT_H_ )
#define _POSITIONCOMPONENT_H_

#include <coment/Component.h>

struct PositionComponent : public coment::Component
{
	PositionComponent() : x(0.f), y(0.f) {}
	PositionComponent(float x, float y) : x(x), y(y) {}

	float x, y;
};

#endif // _POSITIONCOMPONENT_H_