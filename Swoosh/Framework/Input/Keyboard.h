#pragma once

#include <GLFW/glfw3.h>

// Singleton

namespace Swoosh {
	namespace Framework {
		namespace Input {

			class Keyboard
			{
			private:
				// Constructor
				Keyboard(GLFWwindow* window);
				// Functions
				int getKeyState(int keyCode);
				// Variables
				GLFWwindow* m_Window;
			public:
				// Get instance
				static Keyboard &getInstance(GLFWwindow* window);
				// Functions
				bool wasKeyPressed(int keyCode);
				bool wasKeyReleased(int keyCode);
				// Destructor
				~Keyboard();
			};

		}
	}
}