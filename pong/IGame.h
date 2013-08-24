//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _IGAME_H_ )
#define _IGAME_H_

class IGame
{
public:
	virtual void Init( void ) = 0;
	virtual void Update( double dt ) = 0;
	virtual void Render( double frameInterpolation ) = 0;
	virtual void Shutdown( void ) = 0;

	virtual void OnWindowSizeChanged( int newWidth, int newHeight ) = 0;
};

#endif // _IGAME_H_