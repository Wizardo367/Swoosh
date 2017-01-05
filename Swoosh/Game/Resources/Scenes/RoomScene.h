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
	Model* m_Rock1;
	Model* m_Rock2;
	Model* m_Rock3;
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
};
