#include "Framework/Graphics/Skybox.h"
#include "Framework/Graphics/Window.h"
#include "Framework/Input/Keyboard.h"
#include "Framework/Input/Mouse.h"
#include <iostream>
#include "Game/Resources/Scenes/RoomScene.h"
#include "Framework/Graphics/ShaderLib.h"
#include "Framework/Maths/Angle.h"
#include <ctime>

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
	topDownCamera->setPosition(glm::vec3(0, 50, 0));
	topDownCamera->rotate(ang::DEGTORAD(180), ang::DEGTORAD(90));

	Camera* fpCamera = new Camera;

	Camera* currentCamera = topDownCamera;

	// Get keyboard
	Input::Keyboard keyboard = Input::Keyboard::getInstance(window.getGLFWWindow());
	double lastKeyPressTime = time(nullptr);
	float keyWaitingTime = 0.25; // Seconds

	// Update window
	while(!window.hasClosed())
	{
		// Check keyboard for camera switch
		if (keyboard.wasKeyPressed(GLFW_KEY_C) && (time(nullptr) - lastKeyPressTime >= keyWaitingTime))
		{
			lastKeyPressTime = time(nullptr);
			currentCamera = (currentCamera == topDownCamera) ? fpCamera : topDownCamera;
		}

		room->update(currentCamera);
		room->render(currentCamera);
		window.update();
	}

	// Clean-up memory
	delete room;
	delete topDownCamera;
	delete fpCamera;
}
