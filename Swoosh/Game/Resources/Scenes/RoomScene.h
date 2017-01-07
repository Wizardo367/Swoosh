#pragma once

#include "../../../Framework/Graphics/Scene.h"
#include "../../../Framework/Graphics/Skybox.h"
#include "../../../Framework/Graphics/Model.h"
#include "../../../Framework/Input/Keyboard.h"

using namespace Swoosh::Framework;

class RoomScene : public Graphics::Scene
{
private:
	// Variables
	Input::Keyboard* m_Keyboard = nullptr;

	GLSLProgram m_SkyboxProgram;
	GLSLProgram m_ModelProgram;

	Graphics::Skybox* m_Skybox;
	// Models
	Model* m_Bed;
	Model* m_Chair;
	Model* m_Door;
	Model* m_Robot;
	std::array<Model*, 3> m_Rocks;
	Model* m_Table;
	Model* m_TableLamp;
	Model* m_Wardrobe;

	std::vector<Model*> m_FindableObjects;
public:
	RoomScene(GLFWwindow* window);
	~RoomScene();
	// Methods
	virtual void initialise();
	virtual void update(Camera* camera, float deltaTime);
	virtual void render(Camera* camera);
	virtual void setupLighting(Camera* camera);
	virtual void setupDraw(GLSLProgram* program, Model* object, const char* textureVariable, const char* matrixVariable);
};
