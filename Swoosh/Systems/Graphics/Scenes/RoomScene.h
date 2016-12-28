#pragma once

#include "../../../Framework/Graphics/Scene.h"
#include "../../../Framework/Graphics/Skybox.h"

using namespace Swoosh::Framework;

class RoomScene : public Graphics::Scene
{
private:
	// Variables
	GLSLProgram m_SkyboxProgram;
	Graphics::Skybox* m_Skybox;
public:
	RoomScene();
	~RoomScene();
	// Methods
	virtual void initialise();
	virtual void render(Camera camera);
	virtual void setupLighting(Camera camera);
};
