#include "RoomScene.h"
#include "../../../Framework/Graphics/ShaderLib.h"

// Constructor
RoomScene::RoomScene(GLFWwindow* window) : Scene(window)
{
	initialise();

	// Load models
	m_Bed = new Model("../Swoosh/Game/Resources/Models/Maya/bed-m.obj", "", glm::vec3(), glm::vec3(), glm::vec3());
}

// Destructor
RoomScene::~RoomScene()
{
	//delete m_Bed;
	delete m_Skybox;
}

void RoomScene::initialise()
{
	// Link shaders

	// Skybox
	std::vector<const char*> skyboxShaderPaths;
	skyboxShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/skybox.vert");
	skyboxShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/skybox.frag");
	Graphics::Shader::attachShaders(&m_SkyboxProgram, skyboxShaderPaths);

	// Bed
	std::vector<const char*> bedShaderPaths;
	bedShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/bed.vert");
	bedShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/bed.frag");
	Graphics::Shader::attachShaders(&m_BedProgram, bedShaderPaths);

	// Enable depth testing
	gl::Enable(gl::DEPTH_TEST);

	// Create skybox
	m_Skybox = new Graphics::Skybox("../Swoosh/Game/Resources/Textures/Skybox/", "room_", 50);
}

void RoomScene::render(Camera* camera)
{
	// Render objects

	// IMPORTANT
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	// Draw
	m_BedProgram.use();
	setCameraMatrices(&m_BedProgram, camera);
	m_Bed->draw();

	// Skybox
	m_SkyboxProgram.use();
	setCameraMatrices(&m_SkyboxProgram, camera);
	m_SkyboxProgram.setUniform("skybox", m_Skybox->getTexID());
	m_Skybox->render();
}

void RoomScene::setupLighting(Camera* camera)
{
	
}