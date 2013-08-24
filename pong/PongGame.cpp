//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "PongGame.h"
#include <stdlib.h>
#include "coment/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PositionStorageSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/ControlMovementSystem.h"

#include "Managers/BallManager.h"
#include "Managers/PaddleManager.h"

extern int BALL_WIDTH;
extern const int INITIAL_WINDOW_WIDTH;
extern const int INITIAL_WINDOW_HEIGHT;

//-----------------------------------------------------------------------------
static RenderingSystem s_RenderingSystem;
static CollisionSystem s_CollisionSystem;
static PositionStorageSystem s_PositionStorageSystem;
static MovementSystem s_MovementSystem;
static InputSystem s_InputSystem;
static ControlMovementSystem s_ControlMovementSystem;
//-----------------------------------------------------------------------------
static BallManager s_BallManager;
static PaddleManager s_PaddleManager;

//-----------------------------------------------------------------------------
void PongGame::Init( void )
{
	_world.setValue<int>("window_width", INITIAL_WINDOW_WIDTH);
	_world.setValue<int>("window_height", INITIAL_WINDOW_HEIGHT);

	_world.registerSystem(s_RenderingSystem);
	_world.registerSystem(s_CollisionSystem);
	_world.registerSystem(s_MovementSystem);
	_world.registerSystem(s_PositionStorageSystem);
	_world.registerSystem(s_InputSystem);
	_world.registerSystem(s_ControlMovementSystem);

	_world.registerManager(s_BallManager);
	_world.registerManager(s_PaddleManager);

	s_BallManager.createBall();
	s_PaddleManager.createPaddles();
}

//-----------------------------------------------------------------------------
void PongGame::Shutdown( void )
{
}

//-----------------------------------------------------------------------------
void PongGame::Update( double dt )
{
	_world.loopStart();
	_world.setDelta( dt );

	s_PositionStorageSystem.update();
	s_InputSystem.update();
	s_MovementSystem.update();
	s_ControlMovementSystem.update();
	s_CollisionSystem.update();
}

//-----------------------------------------------------------------------------
void PongGame::Render( double frameInterpolation )
{
	_world.setValue<double>("frame_interpolation", frameInterpolation);

	s_RenderingSystem.update();
}

//-----------------------------------------------------------------------------
void PongGame::OnWindowSizeChanged( int newWidth, int newHeight )
{
	_world.setValue<int>("window_width", newWidth);
	_world.setValue<int>("window_height", newHeight);

	s_RenderingSystem.OnWindowSizeChanged( newWidth, newHeight );
}

//-----------------------------------------------------------------------------
void PongGame::OnKeyPressed( int key )
{
	s_InputSystem.OnKeyPressed(key);
}

//-----------------------------------------------------------------------------
void PongGame::OnKeyReleased( int key )
{
	s_InputSystem.OnKeyReleased(key);
}