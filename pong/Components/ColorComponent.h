//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _COLORCOMPONENT_H_ )
#define _COLORCOMPONENT_H_

#include <coment/Component.h>

struct ColorComponent : public coment::Component
{
	ColorComponent() : r(0), g(0), b(0) {}
	ColorComponent(int r, int g, int b) : r(r), g(g), b(b) {}

	int r, g, b;
};

#endif // _COLORCOMPONENT_H_