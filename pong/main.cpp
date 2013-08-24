#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "PongGame.h"

// Thanks, Obama
#ifdef _MSC_VER
	#define snprintf_s _snprintf_s
#endif

GLFWwindow *s_Window = NULL;
static IGame *s_Game = NULL;
int BALL_WIDTH = 10;
extern const int INITIAL_WINDOW_WIDTH = 1600;
extern const int INITIAL_WINDOW_HEIGHT = 900;

static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	if ( s_Game )
	{
		s_Game->OnWindowSizeChanged( width, height );
	}
}

bool Init(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return false;

	s_Window = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Pong", NULL, NULL);
	if (!s_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(s_Window, window_size_callback);
	glfwMakeContextCurrent(s_Window);
	glfwSetKeyCallback(s_Window, key_callback);

	return true;
}

double time()
{
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0)
	{
		QueryPerformanceCounter((LARGE_INTEGER*) &start);
		QueryPerformanceFrequency((LARGE_INTEGER*) &frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*) &counter);
	return (double) ((counter - start) / double(frequency));
}

int main(void)
{
	if (!Init())
	{
		exit(EXIT_FAILURE);
	}

	srand((unsigned) time(0));

	s_Game = new PongGame();
	s_Game->Init();

	// Call once now for initial display
	window_size_callback(s_Window, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);

	double currentTime = 0.0;
	double accumulator = 0.0;

	const double dt = 0.01;
	double t = 0.0;
	int frames = 0;
	double lastFPStime = 0.0;

	bool running = true;
	while (running)
	{
		const double newTime = time();
		double deltaTime = newTime - currentTime;
		currentTime = newTime;

		if (deltaTime > 0.25f)
			deltaTime = 0.25f;

		accumulator += deltaTime;
		
		while (accumulator >= dt)
		{
			accumulator -= dt;
			s_Game->Update( dt );
			t += dt;
		}

		s_Game->Render( accumulator / dt );
		glfwPollEvents();

		++frames;
		if (t - lastFPStime > 1.f)
		{
			const int titleBufferLen = 256;
			char titleBuffer[titleBufferLen];
			_snprintf_s(titleBuffer, titleBufferLen, "Pong | FPS: %d", frames);

			frames = 0;
			lastFPStime = t;
			glfwSetWindowTitle( s_Window, titleBuffer );
		}
		running = running && !glfwWindowShouldClose(s_Window);
	}

	s_Game->Shutdown();

	glfwDestroyWindow(s_Window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}