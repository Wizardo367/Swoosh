#include "Mouse.h"

namespace Swoosh {
	namespace Framework {
		namespace Input {

			// Constructor
			Mouse::Mouse(GLFWwindow* window)
			{
				// Variable initialisation
				m_Window = window;
			}

			// Destructor
			Mouse::~Mouse()
			{
			}

			// Get instance
			Mouse& Mouse::getInstance(GLFWwindow* window)
			{
				static Mouse instance(window);
				return instance;
			}

			// Functions

			int Mouse::getButtonState(int button)
			{
				return glfwGetMouseButton(m_Window, button);
			}

			bool Mouse::wasButtonClicked(int button)
			{
				int state = getButtonState(button);
				return (state == GLFW_PRESS);
			}

			bool Mouse::wasButtonReleased(int button)
			{
				int state = getButtonState(button);
				return (state == GLFW_RELEASE);
			}

		}
	}
}