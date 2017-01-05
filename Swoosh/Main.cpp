#include "Framework/Graphics/Skybox.h"
#include "Framework/Graphics/Window.h"
#include "Framework/Input/Keyboard.h"
#include "Framework/Input/Mouse.h"
#include <iostream>
#include "Game/Resources/Scenes/RoomScene.h"
#include "Framework/Graphics/ShaderLib.h"

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);
	// Create scene
	RoomScene* room = new RoomScene(window.getGLFWWindow());
	
	// Setup cameras
	
	Camera* mainCamera = new Camera;
	mainCamera->zoom(-10.f);

	Camera* fpCamera = new Camera;

	Camera* currentCamera = mainCamera;

	// Update window
	while(!window.hasClosed())
	{
		// Check keyboard for camera switch

		room->update(currentCamera);
		room->render(currentCamera);
		window.update();
	}

	// Clean-up memory
	delete room;
	delete mainCamera;
	delete fpCamera;
}
