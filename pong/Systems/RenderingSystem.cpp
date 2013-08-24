//-----------------------------------------------------------------------------
// Author: Andrew Orner <github@ssba.hey.nu>
//-----------------------------------------------------------------------------
#include "RenderingSystem.h"

#include <coment/World.h>

#include "Components/PositionComponent.h"
#include "Components/BoundsComponent.h"
#include "Components/ColorComponent.h"
#include "Components/PreviousUpdatePositionComponent.h"

#include <GLFW/glfw3.h>

//-----------------------------------------------------------------------------
extern GLFWwindow *s_Window;

//-----------------------------------------------------------------------------
void RenderingSystem::registerComponents( void )
{
	registerComponent<PositionComponent>();
	registerComponent<ColorComponent>();
	registerComponent<BoundsComponent>();
	registerComponent<PreviousUpdatePositionComponent>();
}

//-----------------------------------------------------------------------------
void RenderingSystem::onBegin( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
}

//-----------------------------------------------------------------------------
void RenderingSystem::process(const coment::Entity& e)
{
	PreviousUpdatePositionComponent *lastPosition = _world->getComponent<PreviousUpdatePositionComponent>(e);
	PositionComponent *position = _world->getComponent<PositionComponent>(e);
	BoundsComponent *bounds = _world->getComponent<BoundsComponent>(e);
	ColorComponent *color = _world->getComponent<ColorComponent>(e);

	double interpolation = _world->getValue<double>("frame_interpolation");
	float x = interpolate(lastPosition->x, position->x, interpolation);
	float y = interpolate(lastPosition->y, position->y, interpolation);

	glBegin(GL_POLYGON);
	glColor3ub(color->r, color->g, color->b);
	glVertex3f(x, y, 0.f);
	glVertex3f(x + bounds->width, y, 0.f);
	glVertex3f(x + bounds->width, bounds->height + y, 0.f);
	glVertex3f(x, bounds->height + y, 0.f);
	glEnd();
}

//-----------------------------------------------------------------------------
void RenderingSystem::onEnd( void )
{
	glfwSwapBuffers( s_Window );
}

//-----------------------------------------------------------------------------
float RenderingSystem::interpolate( float a, float b, double alpha ) const
{
	return a * (1.0 - alpha) + b * alpha;
}

//-----------------------------------------------------------------------------
void RenderingSystem::OnWindowSizeChanged( int newWidth, int newHeight )
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, newWidth, 0, newHeight, 1.f, -1.f);
}