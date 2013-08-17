//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _GAMESTATEMANAGER_H_ )
#define _GAMESTATEMANAGER_H_

#include "IGameStateManager.h"

class GameStateManager : public IGameStateManager
{
public:
	virtual void StoreCurrentState( void ) { _previousState = _currentState; }

	virtual GameState &GetCurrentState( void ) { return _currentState; }
	virtual void GetInterpolatedState( float interpolation, GameState &outState ) const;

private:
	GameState _previousState;
	GameState _currentState;
};

#endif // _GAMESTATEMANAGER_H_