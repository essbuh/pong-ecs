#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "PongGame.h"

GLFWwindow *s_Window = NULL;
int BALL_WIDTH = 10;
int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;

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
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 1.f, -1.f);
}

bool Init(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return false;

	s_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong", NULL, NULL);
	if (!s_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(s_Window, window_size_callback);
	glfwMakeContextCurrent(s_Window);
	glfwSetKeyCallback(s_Window, key_callback);

	// Call once now for initial display
	window_size_callback(s_Window, WINDOW_WIDTH, WINDOW_HEIGHT);

	return true;
}

float time()
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
	return (float) ((counter - start) / double(frequency));
}

int main(void)
{
	if (!Init())
	{
		exit(EXIT_FAILURE);
	}

	srand((unsigned) time(0));

	IGame *game = new PongGame();
	game->Init();

	float currentTime = 0.0f;
	float accumulator = 0.0f;

	const float dt = 0.01f;
	float t = 0.0f;
	int frames = 0;

	bool running = true;
	while (running)
	{
		const float newTime = time();
		float deltaTime = newTime - currentTime;
		currentTime = newTime;

		if (deltaTime > 0.25f)
			deltaTime = 0.25f;

		accumulator += deltaTime;
		
		while (accumulator >= dt)
		{
			accumulator -= dt;
			game->Update();
			t += dt;
		}

		game->Render( accumulator / dt );
		glfwPollEvents();

		++frames;
		running = running && !glfwWindowShouldClose(s_Window);
	}

	game->Shutdown();

	glfwDestroyWindow(s_Window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}