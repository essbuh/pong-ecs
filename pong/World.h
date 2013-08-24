//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _WORLD_H_ )
#define _WORLD_H_

class Entity;

class World
{
public:
	void Init( void );
	void Update( void );

	Entity CreateEntity();

private:
};

#endif // _WORLD_H_