#include "Framework/Graphics/Skybox.h"
#include "Framework/Graphics/Window.h"
#include "Framework/Input/Keyboard.h"
#include "Framework/Input/Mouse.h"
#include <iostream>
#include "Game/Resources/Scenes/RoomScene.h"

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);
	RoomScene* room = new RoomScene(window.getGLFWWindow());
	Camera* camera = new Camera;

	// Update window
	while(!window.hasClosed())
	{
		room->update(camera);
		room->render(camera);
		window.update();
	}
}