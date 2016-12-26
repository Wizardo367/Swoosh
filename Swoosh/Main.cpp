#include "Framework/Graphics/Window.h"
#include "Framework/Input/Keyboard.h"
#include <iostream>
#include "Framework/Input/Mouse.h"

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);
	Input::Keyboard keyboard = Input::Keyboard::getInstance(window.getGLFWWindow());
	Input::Mouse mouse = Input::Mouse::getInstance(window.getGLFWWindow());

	// Update window
	while(!window.hasClosed())
	{
		if (keyboard.wasKeyPressed(GLFW_KEY_E) || mouse.wasButtonClicked(GLFW_MOUSE_BUTTON_LEFT))
			std::cout << "Input Detected" << std::endl;
		window.update();
	}
}
