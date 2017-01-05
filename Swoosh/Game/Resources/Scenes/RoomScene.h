#pragma once

#include "../../../Framework/Graphics/Scene.h"
#include "../../../Framework/Graphics/Skybox.h"
#include "../../../Framework/Graphics/Model.h"

using namespace Swoosh::Framework;

class RoomScene : public Graphics::Scene
{
private:
	// Variables
	GLSLProgram m_SkyboxProgram;
	GLSLProgram m_ModelProgram;

	Graphics::Skybox* m_Skybox;
	// Models
	Model* m_Bed;
	Model* m_Chair;
	std::array<Model*, 3> m_Rocks;
	Model* m_Table;
	Model* m_TableLamp;
	Model* m_Wardrobe;
public:
	RoomScene(GLFWwindow* window);
	~RoomScene();
	// Methods
	virtual void initialise();
	virtual void render(Camera* camera);
	virtual void setupLighting(Camera* camera);
	virtual void setupDraw(GLSLProgram* program, Model* object, const char* textureVariable, const char* matrixVariable);
};
