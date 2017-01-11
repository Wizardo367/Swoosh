#include "Timer.h"
#include <GLFW/glfw3.h>

// Constructor
Timer::Timer()
{
	reset();
}

// Destructor
Timer::~Timer()
{
}

void Timer::reset()
{
	m_LastTime = glfwGetTime();
}

float Timer::getDeltaTime()
{
	float delta = glfwGetTime() - m_LastTime;
	m_LastTime = glfwGetTime();
	return delta;
}