//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#if !defined( _INPUTSYSTEM_H_ )
#define _INPUTSYSTEM_H_

#include <coment/systems/EntityProcessingSystem.h>
#include <coment/utils/Bitset.h>

#define KEY_BIT_SIZE 352

class InputSystem : public coment::EntityProcessingSystem
{
public:
	void registerComponents( void );

	virtual void process(const coment::Entity& e);

	void OnKeyPressed(int key) {
		_keyState.setBit(key); 
	}

	void OnKeyReleased(int key) { 
		_keyState.clearBit(key); 
	}

private:
	coment::Bitset<KEY_BIT_SIZE> _keyState;
};

#endif // _INPUTSYSTEM_H_