#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Swoosh {
	namespace Framework {
		namespace Graphics {

			class Window
			{
			private:
				// Members
				const char* m_Title;
				int m_Width, m_Height;
				GLFWwindow* m_Window;
				// Functions
				bool initialiseWindow();
			public:
				// Constructor / Destructor
				Window(const char* title, const int width, const int height, const GLboolean resizeable);
				~Window();
				// Functions
				bool hasClosed();
				GLFWwindow* getGLFWWindow();
				// Methods
				void clear();
				void update();
			};

		}
	}
}