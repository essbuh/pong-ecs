//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _IGAMESTATEMANAGER_H_ )
#define _IGAMESTATEMANAGER_H_

#include "GameState.h"

class IGameStateManager
{
public:
	virtual void StoreCurrentState( void ) = 0;

	virtual GameState &GetCurrentState( void ) = 0;
	virtual void GetInterpolatedState( float interpolation, GameState &outState ) const = 0;
};

#endif // _IGAMESTATEMANAGER_H_