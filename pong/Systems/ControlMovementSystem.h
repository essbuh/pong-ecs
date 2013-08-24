//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _CONTROLMOVEMENTSYSTEM_H_ )
#define _CONTROLMOVEMENTSYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>

class ControlMovementSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);
};

#endif // _CONTROLMOVEMENTSYSTEM_H_