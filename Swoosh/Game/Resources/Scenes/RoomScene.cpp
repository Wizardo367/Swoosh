#include "RoomScene.h"
#include "../../../Framework/Graphics/ShaderLib.h"
#include <valarray>

// Constructor
RoomScene::RoomScene(GLFWwindow* window) : Scene(window)
{
	// Initialise variables
	m_Keyboard = &Input::Keyboard::getInstance(window);

	// Load models
	m_Bed = new Model("../Swoosh/Game/Resources/Models/bed.obj", "../Swoosh/Game/Resources/Textures/Models/Bed/bed.jpg", glm::vec3(0, -74.911, 47.144), 180, glm::vec3(0, 1, 0), glm::vec3(10));
	m_Chair = new Model("../Swoosh/Game/Resources/Models/chair.obj", "../Swoosh/Game/Resources/Textures/Models/Chair/chair.jpg", glm::vec3(25, -68.591, -58.424), 180, glm::vec3(0, 1, 0), glm::vec3(0.8, 0.6, 0.8));
	m_Door = new Model("../Swoosh/Game/Resources/Models/door.obj", "../Swoosh/Game/Resources/Textures/Models/Door/door.jpg", glm::vec3(-25, -75, -75.1), 0, glm::vec3(), glm::vec3(1));
	m_Robot = new Model("../Swoosh/Game/Resources/Models/robot.obj", "../Swoosh/Game/Resources/Textures/Models/Robot/robot.jpg", glm::vec3(0, -72, 0), 0, glm::vec3(), glm::vec3(0.01));

	m_Rocks.at(0) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(33.83, -74.752, -68.498), 0, glm::vec3(), glm::vec3(1));
	m_Rocks.at(1) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(11.775, -68.981, 71.981), 32.621, glm::vec3(0, 1, 0), glm::vec3(0.25));
	m_Rocks.at(2) = new Model("../Swoosh/Game/Resources/Models/rock.obj", "../Swoosh/Game/Resources/Textures/Models/Rock/rock.jpg", glm::vec3(-66.145, -68.337, -3.451), 0, glm::vec3(), glm::vec3(0.15, 0.1, 0.1));

	m_Table = new Model("../Swoosh/Game/Resources/Models/table.obj", "../Swoosh/Game/Resources/Textures/Models/Table/table.jpg", glm::vec3(25, -75, -68), 0, glm::vec3(), glm::vec3(0.15));
	m_DeskLamp = new Model("../Swoosh/Game/Resources/Models/table_lamp.obj", "../Swoosh/Game/Resources/Textures/Models/Table Lamp/table_lamp.jpg", glm::vec3(18.342, -64.05, -70.186), -45, glm::vec3(0, 1, 0), glm::vec3(0.05));
	m_Wardrobe = new Model("../Swoosh/Game/Resources/Models/wardrobe.obj", "../Swoosh/Game/Resources/Textures/Models/Wardrobe/wardrobe.jpg", glm::vec3(-67.726, -75, 0), 90, glm::vec3(0, 1, 0), glm::vec3(2));

	initialise();
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
	delete m_DeskLamp;
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

	// Lights
	std::vector<const char*> lightShaderPaths;
	lightShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/deskLight.vert");
	lightShaderPaths.push_back("../Swoosh/Game/Resources/Shaders/deskLight.frag");
	Graphics::Shader::attachShaders(&m_DeskLightProgram, lightShaderPaths);

	// Enable depth testing
	gl::Enable(gl::DEPTH_TEST);

	// Create skybox
	m_Skybox = new Graphics::Skybox("../Swoosh/Game/Resources/Textures/Skybox/", "room_", 75);

	// Define findable objects
	for (Model* rock : m_Rocks)
		m_FindableObjects.push_back(rock);
}

void RoomScene::update(Camera* camera, float deltaTime)
{
	// Base update
	Scene::update(camera, deltaTime);

	// Check for proximity to objects

	const float minProx = 35;

	if (m_FindableObjects.size() != 0)
	{
		for (int i = 0; i < m_FindableObjects.size(); i++)
		{
			// Get pointer
			Model* findable = m_FindableObjects.at(i);

			// Get distance
			glm::vec3 calc = m_Robot->getPosition() - findable->getPosition();
			float distSquared = glm::dot(calc, calc);
			if (distSquared < 0) distSquared *= 1;

			std::cout << distSquared << "\n";

			// Remove object if params are met
			if (distSquared <= minProx)
			{
				m_Rocks.at(i) = nullptr;
				m_FindableObjects.erase(m_FindableObjects.begin() + i);
			}
		}
	}

	// Check for keyboard input
	float movementSpeed = 5.f * deltaTime;
	float robotAngle = m_Robot->getRotationAngle();
	glm::vec3 movement = glm::vec3(movementSpeed * std::cos(robotAngle), 0, movementSpeed * std::sin(-robotAngle));
	float rotationIncrement = 3.f * deltaTime;

	bool robotRotated = false;
	bool robotMoved = false;

	// Rotate robot
	if (m_Keyboard->wasKeyPressed(GLFW_KEY_A))
	{
		m_Robot->setRotation(robotAngle + rotationIncrement, glm::vec3(0, 1, 0));
		robotRotated = true;
	}
	else if (m_Keyboard->wasKeyPressed(GLFW_KEY_D))
	{
		m_Robot->setRotation(robotAngle - rotationIncrement, glm::vec3(0, 1, 0));
		robotRotated = true;
	}

	// Move robot
	if (m_Keyboard->wasKeyPressed(GLFW_KEY_W))
	{
		m_Robot->setPosition(m_Robot->getPosition() + movement);
		robotMoved = true;
	}
	else if (m_Keyboard->wasKeyPressed(GLFW_KEY_S))
	{
		m_Robot->setPosition(m_Robot->getPosition() - movement);
		robotMoved = true;
	}

	// Update camera position and rotation

	const char* cameraID = camera->getID();
	glm::vec3 robotPosition = m_Robot->getPosition();
	glm::vec3 cameraPosition = camera->getPosition();

	robotAngle = -m_Robot->getRotationDifference();
	float cos = std::cos(robotAngle);
	float sin = std::sin(robotAngle);

	// Rotate
	if (robotRotated && cameraID == "follow")
	{
		camera->rotate(robotAngle, 0);
		float newX = robotPosition.x + (cameraPosition.x - robotPosition.x) * cos - (cameraPosition.x - robotPosition.x) * sin;
		float newZ = robotPosition.z + (cameraPosition.z - robotPosition.z) * sin + (cameraPosition.z - robotPosition.z) * cos;
		m_Robot->setPosition(glm::vec3(newX, robotPosition.y, newZ));
	}

	// Move
	camera->setPosition(glm::vec3(robotPosition.x, camera->getPosition().y, robotPosition.z));

	// Update matrix
	m_Robot->updateTransformationMatrix();
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
		// Check for null
		if (rock == nullptr) continue;

		setupDraw(&m_ModelProgram, rock, textureVariable, matrixVariable);
		rock->draw();
	}

	setupDraw(&m_ModelProgram, m_Table, textureVariable, matrixVariable);
	m_Table->draw();

	setupDraw(&m_ModelProgram, m_DeskLamp, textureVariable, matrixVariable);
	m_DeskLamp->draw();

	setupDraw(&m_ModelProgram, m_Wardrobe, textureVariable, matrixVariable);
	m_Wardrobe->draw();

	// Skybox
	m_SkyboxProgram.use();
	setCameraMatrices(&m_SkyboxProgram, camera);
	m_SkyboxProgram.setUniform("skybox", m_Skybox->getTexID());
	m_Skybox->render();

	// Lights
	m_DeskLightProgram.use();
	setCameraMatrices(&m_DeskLightProgram, camera);

	vec4 lightPos = vec4(camera->getPosition(), 1.f);
	vec4 target = vec4(0.f, 0.f, 0.f, 1.f);
	mat4 mv = camera->getView() * m_ModelMatrix;
	m_DeskLightProgram.setUniform("lightDirection", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])) * vec3(target - lightPos));
	m_DeskLightProgram.setUniform("lightPos", mv * lightPos);
	m_DeskLightProgram.setUniform("eyePos", camera->getPosition());
}

void RoomScene::setupLighting(GLSLProgram* program, Camera* camera)
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