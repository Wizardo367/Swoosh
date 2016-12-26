#include "Keyboard.h"

namespace Swoosh {
	namespace Framework {
		namespace Input {

			// Constructor
			Keyboard::Keyboard(GLFWwindow* window)
			{
				// Variable initialisation
				m_Window = window;
			}

			// Destructor
			Keyboard::~Keyboard()
			{
			}

			// Get instance
			Keyboard& Keyboard::getInstance(GLFWwindow* window)
			{
				static Keyboard instance(window);
				return instance;
			}

			// Functions

			int Keyboard::getKeyState(int keyCode)
			{
				return glfwGetKey(m_Window, keyCode);
			}

			bool Keyboard::wasKeyPressed(int keyCode)
			{
				int state = getKeyState(keyCode);
				return (state == GLFW_PRESS);
			}

			bool Keyboard::wasKeyReleased(int keyCode)
			{
				int state = getKeyState(keyCode);
				return (state == GLFW_RELEASE);
			}

		}
	}
}