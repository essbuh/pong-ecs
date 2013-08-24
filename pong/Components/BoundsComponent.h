//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _BOUNDSCOMPONENT_H_ )
#define _BOUNDSCOMPONENT_H_

#include <coment/Component.h>

struct BoundsComponent : public coment::Component
{
	BoundsComponent() : width(0.f), height(0.f) {}
	BoundsComponent(float width, float height) : width(width), height(height) {}

	float width, height;
};

#endif // _BOUNDSCOMPONENT_H_