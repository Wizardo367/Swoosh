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
	GLSLProgram m_BedProgram;
	Graphics::Skybox* m_Skybox;
	// Models
	Model* m_Bed;
public:
	RoomScene(GLFWwindow* window);
	~RoomScene();
	// Methods
	virtual void initialise();
	virtual void render(Camera* camera);
	virtual void setupLighting(Camera* camera);
};
