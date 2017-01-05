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

			glm::vec2 Mouse::getDeltaMousePosition()
			{
				double posX, posY;
				glfwGetCursorPos(m_Window, &posX, &posY);
				// Get delta movement
				double deltaX, deltaY;
				deltaX = (m_LastPosX - posX);
				deltaY = (m_LastPosY - posY);
				// Store position
				m_LastPosX = posX;
				m_LastPosY = posY;
				return glm::vec2(deltaX, deltaY);
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