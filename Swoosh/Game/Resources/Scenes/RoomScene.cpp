#include "RoomScene.h"
#include "../../../Framework/Graphics/ShaderLib.h"

// Constructor
RoomScene::RoomScene(GLFWwindow* window) : Scene(window)
{
	initialise();

	// Load models
	m_Bed = new Model("../Swoosh/Game/Resources/Models/Maya/bed-m.obj", "../Swoosh/Game/Resources/Textures/Models/Bed/bed.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Chair = new Model("../Swoosh/Game/Resources/Models/Maya/chair-m.obj", "../Swoosh/Game/Resources/Textures/Models/Chair/chair.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Rock1 = new Model("../Swoosh/Game/Resources/Models/Maya/rock-1-m.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Rock2 = new Model("../Swoosh/Game/Resources/Models/Maya/rock-2-m.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Rock3 = new Model("../Swoosh/Game/Resources/Models/Maya/rock-3-m.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Table = new Model("../Swoosh/Game/Resources/Models/Maya/table-m.obj", "../Swoosh/Game/Resources/Textures/Models/Table/table.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_TableLamp = new Model("../Swoosh/Game/Resources/Models/Maya/table_lamp-m.obj", "../Swoosh/Game/Resources/Textures/Models/Table Lamp/table_lamp.jpg", glm::vec3(), glm::vec3(), glm::vec3());
	m_Wardrobe = new Model("../Swoosh/Game/Resources/Models/Maya/wardrobe-m.obj", "../Swoosh/Game/Resources/Textures/Models/Wardrobe/wardrobe.jpg", glm::vec3(), glm::vec3(), glm::vec3());
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

	// Models
	std::vector<const char*> modelShaderPaths;
	modelShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/model.vert");
	modelShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/model.frag");

	Graphics::Shader::attachShaders(&m_ModelProgram, modelShaderPaths);

	// Enable depth testing
	gl::Enable(gl::DEPTH_TEST);

	// Create skybox
	m_Skybox = new Graphics::Skybox("../Swoosh/Game/Resources/Textures/Skybox/", "room_", 75);
}

void RoomScene::render(Camera* camera)
{
	// Render objects

	// IMPORTANT
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	// Draw
	m_ModelProgram.use();
	setCameraMatrices(&m_ModelProgram, camera);

	m_ModelProgram.setUniform("modelTexture", m_Bed->getTexID());
	m_Bed->draw();

	m_ModelProgram.setUniform("modelTexture", m_Chair->getTexID());
	m_Chair->draw();

	m_ModelProgram.setUniform("modelTexture", m_Rock1->getTexID());
	m_Rock1->draw();
	m_Rock2->draw();
	m_Rock3->draw();

	m_ModelProgram.setUniform("modelTexture", m_Table->getTexID());
	m_Table->draw();

	m_ModelProgram.setUniform("modelTexture", m_TableLamp->getTexID());
	m_TableLamp->draw();

	m_ModelProgram.setUniform("modelTexture", m_Wardrobe->getTexID());
	m_Wardrobe->draw();

	// Skybox
	m_SkyboxProgram.use();
	setCameraMatrices(&m_SkyboxProgram, camera);
	m_SkyboxProgram.setUniform("skybox", m_Skybox->getTexID());
	m_Skybox->render();
}

void RoomScene::setupLighting(Camera* camera)
{
	
}