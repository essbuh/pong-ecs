#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static GLFWwindow *s_Window = NULL;
const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAME_SKIP = 5;
const int BALL_WIDTH = 10;

typedef struct state_s {

	float x;
	float y;
	float dx;
	float dy;

	state_s() {
		x = 0.f;
		y = 0.f;
		dx = 0.f;
		dy = 0.f;
	}

} state_s;

static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Init(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return false;

	s_Window = glfwCreateWindow(640, 480, "Pong", NULL, NULL);
	if (!s_Window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(s_Window);
	glfwSetKeyCallback(s_Window, key_callback);

	glfwSwapInterval(0);

	return true;
}

void Update(state_s &state)
{
	state.x += state.dx;
	state.y += state.dy;

	int width, height;
	glfwGetFramebufferSize(s_Window, &width, &height);

	if (state.x < 0)
	{
		state.x = 0;
		state.dx = -state.dx;
	}
	else if ((state.x + BALL_WIDTH) >= width)
	{
		state.x = width - BALL_WIDTH;
		state.dx = -state.dx;
	}

	if (state.y < 0)
	{
		state.y = 0;
		state.dy = -state.dy;
	}
	else if ((state.y + BALL_WIDTH) >= height)
	{
		state.y = height - BALL_WIDTH;
		state.dy = -state.dy;
	}
}

void Render(const state_s &state)
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(s_Window, &width, &height);
	ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640.f, 0, 480.f, 1.f, -1.f);
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
	glfwPollEvents();
}

const state_s InterpolateState(const state_s &previous, const state_s &current, double interpolation)
{
	state_s state;
	state.x = current.x * interpolation + previous.x * (1.0 - interpolation);
	state.y = current.y * interpolation + previous.y * (1.0 - interpolation);
	return state;
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

	double currentTime = 0.0f;
	double accumulator = 0.0f;

	const double dt = 0.01;
	double t = 0.0;
	
	state_s previous;
	state_s current;
	int frames = 0;

	srand((unsigned) time(0));
	do
	{
		current.dx = 2.f * (-1.f + (float) rand() / ((float) RAND_MAX / (2.f)));
		current.dy = 2.f * (-1.f + (float) rand() / ((float) RAND_MAX / (2.f)));
	} while (current.dx == 0.f && current.dy == 0.f);

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
			previous = current;
			Update(current);
			t += dt;
		}

		const state_s state = InterpolateState(previous, current, accumulator / dt);
		Render(state);

		++frames;
		running = running && !glfwWindowShouldClose(s_Window);
	}

	glfwDestroyWindow(s_Window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}