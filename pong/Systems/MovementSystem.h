//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _MOVEMENTSYSTEM_H_ )
#define _MOVEMENTSYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>

class MovementSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);
};

#endif // _MOVEMENTSYSTEM_H_