#include "RoomScene.h"

// Constructor
RoomScene::RoomScene()
{
	initialise();
}

// Destructor
RoomScene::~RoomScene()
{
	delete m_Skybox;
}

void RoomScene::initialise()
{
	// Link shaders
	std::vector<const char*> shaderPaths;
	shaderPaths.push_back("../Swoosh/Game/Resources/Shaders/skybox.vert");
	shaderPaths.push_back("../Swoosh/Game/Resources/Shaders/skybox.frag");
	linkShaders(&m_SkyboxProgram, shaderPaths);

	// Enable depth testing
	gl::Enable(gl::DEPTH_TEST);

	// Create skybox
	m_Skybox = new Graphics::Skybox("../Swoosh/Game/Resources/Textures/Skybox/", "room_", 1);
}

void RoomScene::render(Camera camera)
{
	// TODO Check if this is needed
	// Clear buffers
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	// TODO Render other objects here

	// Skybox
	m_SkyboxProgram.use();
	m_ModelMatrix = mat4(1.0f);
	setCameraMatrices(&m_SkyboxProgram, camera);
	m_SkyboxProgram.setUniform("skybox", m_Skybox->getTexID());
	m_Skybox->render();
}

void RoomScene::setupLighting(Camera camera)
{
	
}