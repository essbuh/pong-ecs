//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _PONGGAME_H_ )
#define _PONGGAME_H_

#include "IGame.h"
#include "coment/World.h"

class PongGame : public IGame
{
public:
	virtual void Init( void );
	virtual void Update( double dt );
	virtual void Render( double frameInterpolation );
	virtual void Shutdown( void );

	virtual void OnWindowSizeChanged( int newWidth, int newHeight );
	virtual void OnKeyPressed( int key );
	virtual void OnKeyReleased( int key );

private:
	coment::World _world;
};

#endif // _PONGGAME_H_