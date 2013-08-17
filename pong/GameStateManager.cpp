//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "GameStateManager.h"

//-----------------------------------------------------------------------------
void GameStateManager::GetInterpolatedState( float clampedPercent, GameState &outState ) const
{
	outState.x = _currentState.x * clampedPercent + _previousState.x * (1.0 - clampedPercent);
	outState.y = _currentState.y * clampedPercent + _previousState.y * (1.0 - clampedPercent);
}