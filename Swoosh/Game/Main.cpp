#include "../Framework/Graphics/Skybox.h"
#include "../Framework/Graphics/Window.h"
#include "../Framework/Input/Keyboard.h"
#include <iostream>
#include "../Game/Resources/Scenes/RoomScene.h"
#include "../Framework/Graphics/ShaderLib.h"
#include "../Framework/Maths/Angle.h"
#include <ctime>
#include "../Framework/Utilities/Timer.h"

int main()
{
	using namespace Swoosh;
	using namespace Framework;

	// Create window
	Graphics::Window window("OpenGL Robot", 960, 540, false);
	// Create scene
	RoomScene* room = new RoomScene(window.getGLFWWindow());
	
	// Setup cameras
	
	Camera* topDownCamera = new Camera("topDown");
	topDownCamera->setPosition(glm::vec3(0, 50, 0));
	topDownCamera->rotate(ang::DEGTORAD(180), ang::DEGTORAD(90));

	Camera* followCamera = new Camera("follow");
	followCamera->setPosition(glm::vec3(-10, -68, 0));
	followCamera->rotate(ang::DEGTORAD(90), ang::DEGTORAD(15));

	Camera* currentCamera = topDownCamera;

	// Get keyboard
	Input::Keyboard keyboard = Input::Keyboard::getInstance(window.getGLFWWindow());
	double lastCameraKeyPressTime = time(nullptr);
	float keyWaitingTime = 0.25; // Seconds

	// Timer
	Timer timer;

	// Update window
	while(!window.hasClosed())
	{
		float deltaTime = timer.getDeltaTime();

		// Check keyboard for camera switch
		if (keyboard.wasKeyPressed(GLFW_KEY_C) && (time(nullptr) - lastCameraKeyPressTime >= keyWaitingTime))
		{
			lastCameraKeyPressTime = time(nullptr);
			currentCamera = (currentCamera == topDownCamera) ? followCamera : topDownCamera;
		}

		room->update(currentCamera, deltaTime);
		room->render(currentCamera);
		window.update();
	}

	// Clean-up memory
	delete room;
	delete topDownCamera;
	delete followCamera;
}