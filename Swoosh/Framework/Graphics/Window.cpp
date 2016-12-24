#include "Window.h"
#include <iostream>

namespace Swoosh {
	namespace Framework {
		namespace Graphics {

			// Constructor
			Window::Window(const char* title, const int width, const int height, const GLboolean resizeable)
			{
				// Variable initialisation
				m_Title = title;
				m_Width = width;
				m_Height = height;

				// GLFW initialisation
				glfwInit();
				// GLFW setup
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_RESIZABLE, resizeable);

				// If window is resizeable, then call resize method on resize
				//if (resizeable)
					//glfwSetWindowSizeCallback(m_Window, )

				// Create window
				if (!initialiseWindow())
				{
					glfwTerminate(); // Terminates library
					return;
				}
			}

			// Destructor
			Window::~Window()
			{
				glfwTerminate(); // Terminates library
			}

			// Initialise window
			bool Window::initialiseWindow()
			{
				// Create window
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
				
				// Check for error
				if (!m_Window)
				{
					std::cerr << "Error: Window Creation Failed!" << "\n";
					return false;
				}

				// Set properties
				glfwMakeContextCurrent(m_Window);

				return true;
			}

			// Update
			void Window::update()
			{
				glfwPollEvents(); // Get events
				//glViewport(0, 0, m_Width, m_Height);
				glfwSwapBuffers(m_Window); // Swap buffers
			}

			// Closed
			bool Window::hasClosed()
			{
				return glfwWindowShouldClose(m_Window);
			}

		}
	}
}
