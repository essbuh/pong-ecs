//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "PongGame.h"
#include "GameStateManager.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

extern GLFWwindow *s_Window;

extern int BALL_WIDTH;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

//-----------------------------------------------------------------------------
void PongGame::Init( void )
{
	_gameStateManager = new GameStateManager();

	GameState &state = _gameStateManager->GetCurrentState();

	do
	{
		state.dx = 2.f * (-1.f + (float) rand() / ((float) RAND_MAX / (2.f)));
		state.dy = 2.f * (-1.f + (float) rand() / ((float) RAND_MAX / (2.f)));
	} while (state.dx == 0.f && state.dy == 0.f);
}

//-----------------------------------------------------------------------------
void PongGame::Shutdown( void )
{
	if ( _gameStateManager )
	{
		delete _gameStateManager;
	}
}

//-----------------------------------------------------------------------------
void PongGame::Update( void )
{
	_gameStateManager->StoreCurrentState();
	
	GameState &state = _gameStateManager->GetCurrentState();
	UpdateGameState( state );
}

//-----------------------------------------------------------------------------
void PongGame::UpdateGameState( GameState &state )
{
	state.x += state.dx;
	state.y += state.dy;

	if (state.x < 0)
	{
		state.x = 0;
		state.dx = -state.dx;
	}
	else if ((state.x + BALL_WIDTH) >= WINDOW_WIDTH)
	{
		state.x = WINDOW_WIDTH - BALL_WIDTH;
		state.dx = -state.dx;
	}

	if (state.y < 0)
	{
		state.y = 0;
		state.dy = -state.dy;
	}
	else if ((state.y + BALL_WIDTH) >= WINDOW_HEIGHT)
	{
		state.y = WINDOW_HEIGHT - BALL_WIDTH;
		state.dy = -state.dy;
	}
}

//-----------------------------------------------------------------------------
void PongGame::Render( float frameInterpolation )
{
	_gameStateManager->GetInterpolatedState( frameInterpolation, _renderState );
	RenderGameState( _renderState );
}

//-----------------------------------------------------------------------------
void PongGame::RenderGameState( const GameState &state )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(state.x, state.y, 0.f);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(BALL_WIDTH, 0.f, 0.f);
	glVertex3f(BALL_WIDTH, BALL_WIDTH, 0.f);
	glVertex3f(0.f, BALL_WIDTH, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();

	glfwSwapBuffers(s_Window);
}