//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _KEYBINDINGCOMPONENT_H_ )
#define _KEYBINDINGCOMPONENT_H_

#include <coment/Component.h>

struct KeyBindingComponent : public coment::Component
{
	KeyBindingComponent() : upKey(0), downKey(0) {}
	KeyBindingComponent(int upKey, int downKey) : upKey(upKey), downKey(downKey) {}

	int upKey, downKey;
};

#endif // _KEYBINDINGCOMPONENT_H_