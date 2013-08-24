//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _PREVIOUSUPDATEPOSITIONCOMPONENT_H_ )
#define _PREVIOUSUPDATEPOSITIONCOMPONENT_H_

#include <coment/Component.h>

//-----------------------------------------------------------------------------
// Component that stores the previous update's Position
struct PreviousUpdatePositionComponent : public coment::Component
{
	PreviousUpdatePositionComponent() : x(0.f), y(0.f) {}
	PreviousUpdatePositionComponent(float x, float y) : x(x), y(y) {}

	float x, y;
};

#endif // _PREVIOUSUPDATEPOSITIONCOMPONENT_H_