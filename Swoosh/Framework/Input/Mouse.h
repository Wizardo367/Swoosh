#pragma once

#include <GLFW/glfw3.h>
#include <glm/detail/type_vec2.hpp>

// Singleton

namespace Swoosh {
	namespace Framework {
		namespace Input {

			class Mouse
			{
			private:
				// Constructor
				Mouse(GLFWwindow* window);
				// Functions
				int getButtonState(int button);
				// Variables
				GLFWwindow* m_Window;
				double m_LastPosX, m_LastPosY;
				float m_Scroll;
			public:
				// Default constructor
				Mouse() {};
				// Get instance
				static Mouse &getInstance(GLFWwindow* window);
				// Functions
				glm::vec2 getDeltaMousePosition();
				bool wasButtonClicked(int button);
				bool wasButtonReleased(int button);
				// Destructor
				~Mouse();
			};

		}
	}
}