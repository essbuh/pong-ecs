//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _PONGGAME_H_ )
#define _PONGGAME_H_

#include "IGame.h"
#include "IGameStateManager.h"

class PongGame : public IGame
{
public:
	virtual void Init( void );
	virtual void Update( void );
	virtual void Render( float frameInterpolation );
	virtual void Shutdown( void );

protected:
	virtual void UpdateGameState( GameState &state );
	virtual void RenderGameState( const GameState &state );

private:
	GameState _renderState;
	IGameStateManager *_gameStateManager;
};

#endif // _PONGGAME_H_