//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "PongGame.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "coment/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PositionStorageSystem.h"

#include "Managers/BallManager.h"

extern GLFWwindow *s_Window;

extern int BALL_WIDTH;
extern const int INITIAL_WINDOW_WIDTH;
extern const int INITIAL_WINDOW_HEIGHT;

//-----------------------------------------------------------------------------
static RenderingSystem s_RenderingSystem;
static CollisionSystem s_CollisionSystem;
static PositionStorageSystem s_PositionStorageSystem;
static MovementSystem s_MovementSystem;
//-----------------------------------------------------------------------------
static BallManager s_BallManager;

//-----------------------------------------------------------------------------
void PongGame::Init( void )
{
	_world.setValue<int>("window_width", INITIAL_WINDOW_WIDTH);
	_world.setValue<int>("window_height", INITIAL_WINDOW_HEIGHT);

	_world.registerSystem(s_RenderingSystem);
	_world.registerSystem(s_CollisionSystem);
	_world.registerSystem(s_MovementSystem);
	_world.registerSystem(s_PositionStorageSystem);

	_world.registerManager(s_BallManager);

	s_BallManager.createBall();
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
	s_MovementSystem.update();
	s_CollisionSystem.update();
}

//-----------------------------------------------------------------------------
void PongGame::Render( double frameInterpolation )
{
	_world.setValue<double>("frame_interpolation", frameInterpolation);

	_world.getSystem<RenderingSystem>()->update();
}

//-----------------------------------------------------------------------------
void PongGame::OnWindowSizeChanged( int newWidth, int newHeight )
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, newWidth, 0, newHeight, 1.f, -1.f);

	_world.setValue<int>("window_width", newWidth);
	_world.setValue<int>("window_height", newHeight);
}