//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _RENDERINGSYSTEM_H_ )
#define _RENDERINGSYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>

class RenderingSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);

	virtual void onBegin( void );
	virtual void onEnd( void );

	void OnWindowSizeChanged( int newWidth, int newHeight );

private:
	float interpolate( float a, float b, double alpha ) const;
};

#endif // _RENDERINGSYSTEM_H_