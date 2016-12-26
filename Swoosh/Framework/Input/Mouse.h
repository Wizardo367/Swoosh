#pragma once

#include <GLFW/glfw3.h>

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
			public:
				// Get instance
				static Mouse &getInstance(GLFWwindow* window);
				// Functions
				bool wasButtonClicked(int button);
				bool wasButtonReleased(int button);
				// Destructor
				~Mouse();
			};

		}
	}
}