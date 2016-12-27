#include "Window.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glew.h>

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

				// Initialise GLLoadGen
				if (gl::sys::LoadFunctions() == nullptr)
				{
					std::cerr << "Error: OpenGL loading failed" << "\n";
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
					std::cerr << "Error: Window creation failed!" << "\n";
					return false;
				}

				// Set properties
				glfwMakeContextCurrent(m_Window);

				return true;
			}

			// Update
			void Window::update()
			{ 
				// Get events
				glfwPollEvents();
				// Swap buffers
				glfwSwapBuffers(m_Window); 
			}

			// Closed
			bool Window::hasClosed()
			{
				return glfwWindowShouldClose(m_Window);
			}
			
			// Get GLFW window
			GLFWwindow* Window::getGLFWWindow()
			{
				return m_Window;
			}

		}
	}
}
