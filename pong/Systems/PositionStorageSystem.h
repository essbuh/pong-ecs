//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _POSITIONSTORAGESYSTEM_H_ )
#define _POSITIONSTORAGESYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>

class PositionStorageSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);
};

#endif // _POSITIONSTORAGESYSTEM_H_