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
	
	Camera* topDownCamera = new Camera;
	//topDownCamera->zoom(-10.f);
	topDownCamera->setPosition(glm::vec3(0, 25, 0));

	Camera* fpCamera = new Camera;

	Camera* currentCamera = topDownCamera;

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
	delete topDownCamera;
	delete fpCamera;
}
