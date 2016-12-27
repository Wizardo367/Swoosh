#include "Framework/Graphics/Skybox.h"
#include "Framework/Graphics/Window.h"
#include "Framework/Input/Keyboard.h"
#include "Framework/Input/Mouse.h"
#include <iostream>

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);
	
	Graphics::Skybox skybox("../Swoosh/Systems/Graphics/Textures/Skybox/", "TowerHousepano_", 10);

	// Update window
	while(!window.hasClosed())
	{
		skybox.render();

		window.update();
	}
}
