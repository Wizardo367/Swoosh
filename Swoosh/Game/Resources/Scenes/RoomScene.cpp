#include "RoomScene.h"
#include "../../../Framework/Graphics/ShaderLib.h"

// Constructor
RoomScene::RoomScene(GLFWwindow* window) : Scene(window)
{
	initialise();

	// Load models
	m_Bed = new Model("../Swoosh/Game/Resources/Models/bed.obj", "../Swoosh/Game/Resources/Textures/Models/Bed/bed.jpg", glm::vec3(0, -74.911, 36.018), 180, glm::vec3(0, 1, 0), glm::vec3(10));
	m_Chair = new Model("../Swoosh/Game/Resources/Models/chair.obj", "../Swoosh/Game/Resources/Textures/Models/Chair/chair.jpg", glm::vec3(25, -68.591, -58.424), 180, glm::vec3(0, 1, 0), glm::vec3(0.8, 0.6, 0.8));
	m_Door = new Model("../Swoosh/Game/Resources/Models/door.obj", "../Swoosh/Game/Resources/Textures/Models/Door/door.jpg", glm::vec3(-25, -75, -75.1), 0, glm::vec3(), glm::vec3(1));
	m_Robot = new Model("../Swoosh/Game/Resources/Models/robot.obj", "../Swoosh/Game/Resources/Textures/Models/Robot/robot.jpg", glm::vec3(0, -67.169, 0), 0, glm::vec3(), glm::vec3(0.01));

	m_Rocks.at(0) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(33.83, -74.752, -68.498), 0, glm::vec3(), glm::vec3(1));
	m_Rocks.at(1) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(11.775, -68.981, 60.856), 32.621, glm::vec3(0, 1, 0), glm::vec3(0.25));
	m_Rocks.at(2) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(-66.145, -62.212, -3.451), 0, glm::vec3(), glm::vec3(0.15, 0.1, 0.1));
	
	m_Table = new Model("../Swoosh/Game/Resources/Models/table.obj", "../Swoosh/Game/Resources/Textures/Models/Table/table.jpg", glm::vec3(25, -75, -68), 0, glm::vec3(), glm::vec3(0.15));
	m_TableLamp = new Model("../Swoosh/Game/Resources/Models/table_lamp.obj", "../Swoosh/Game/Resources/Textures/Models/Table Lamp/table_lamp.jpg", glm::vec3(18.342, -64.05, -70.186), -45, glm::vec3(0, 1, 0), glm::vec3(0.05));
	m_Wardrobe = new Model("../Swoosh/Game/Resources/Models/wardrobe.obj", "../Swoosh/Game/Resources/Textures/Models/Wardrobe/wardrobe.jpg", glm::vec3(-67.726, -75, 0), 90, glm::vec3(0, 1, 0), glm::vec3(2));
}

// Destructor
RoomScene::~RoomScene()
{
	for (int i = 0; i < m_Rocks.size(); i++)
		delete m_Rocks.at(i);
	
	delete m_Bed;
	delete m_Chair;
	delete m_Door;
	delete m_Robot;
	delete m_Table;
	delete m_TableLamp;
	delete m_Wardrobe;
	
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

	const char* textureVariable = "modelTexture";
	const char* matrixVariable = "TransformMatrix";

	// Draw
	m_ModelProgram.use();
	setCameraMatrices(&m_ModelProgram, camera);

	setupDraw(&m_ModelProgram, m_Bed, textureVariable, matrixVariable);
	m_Bed->draw();

	setupDraw(&m_ModelProgram, m_Chair, textureVariable, matrixVariable);
	m_Chair->draw();

	setupDraw(&m_ModelProgram, m_Door, textureVariable, matrixVariable);
	m_Door->draw();

	setupDraw(&m_ModelProgram, m_Robot, textureVariable, matrixVariable);
	m_Robot->draw();

	for (int i = 0; i < m_Rocks.size(); i++)
	{
		Model* rock = m_Rocks.at(i);
		setupDraw(&m_ModelProgram, rock, textureVariable, matrixVariable);
		rock->draw();
	}

	setupDraw(&m_ModelProgram, m_Table, textureVariable, matrixVariable);
	m_Table->draw();

	setupDraw(&m_ModelProgram, m_TableLamp, textureVariable, matrixVariable);
	m_TableLamp->draw();

	setupDraw(&m_ModelProgram, m_Wardrobe, textureVariable, matrixVariable);
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

void RoomScene::setupDraw(GLSLProgram* program, Model* object, const char* textureVariable, const char* matrixVariable)
{
	// Texture
	program->setUniform(textureVariable, object->getTexID());
	// Matrices
	glm::mat4 transformMatrix = object->getTransformMatrix();
	gl::UniformMatrix4fv(gl::GetUniformLocation(program->getHandle(), matrixVariable), 1, gl::FALSE_, &transformMatrix[0][0]);
}