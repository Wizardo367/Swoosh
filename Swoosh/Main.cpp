#include "Framework/Graphics/Window.h"

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);

	// Update window
	while(!window.hasClosed())
	{
		window.update();
	}
}