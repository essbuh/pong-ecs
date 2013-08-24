//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _CONTROLCOMPONENT_H_ )
#define _CONTROLCOMPONENT_H_

#include <coment/Component.h>

struct ControlComponent : public coment::Component
{
	ControlComponent() : up(false), down(false) {}
	ControlComponent(bool up, bool down) : up(up), down(down) {}

	bool up, down;
};

#endif // _CONTROLCOMPONENT_H_