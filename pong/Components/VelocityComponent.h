//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _VELOCITYCOMPONENT_H_ )
#define _VELOCITYCOMPONENT_H_

#include <coment/Component.h>

struct VelocityComponent : public coment::Component
{
	VelocityComponent() : x(0.f), y(0.f) {}
	VelocityComponent(float x, float y) : x(x), y(y) {}

	float x, y;
};

#endif // _VELOCITYCOMPONENT_H_