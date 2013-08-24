//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _COLLISIONSYSTEM_H_ )
#define _COLLISIONSYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>

class CollisionSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);
};

#endif // _COLLISIONSYSTEM_H_