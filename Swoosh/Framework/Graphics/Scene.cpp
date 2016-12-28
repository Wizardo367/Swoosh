#include "Scene.h"
#include <iostream>

// Compile and link shader
void Swoosh::Framework::Graphics::Scene::linkShaders(GLSLProgram* program, std::vector<const char*> paths)
{
	try
	{
		// Compile shaders
		for each (const char* path in paths)
			program->compileShader(path);
		// Link shaders
		program->link();
		program->validate();
	}
	catch (GLSLProgramException& e)
	{
		std::cerr << "Error: Shader linking failed!" << "\n\n";
		std::cerr << e.what() << "\n";
	}
}

// Camera matrices setup
void Swoosh::Framework::Graphics::Scene::setCameraMatrices(GLSLProgram* program, Camera camera)
{
	mat4 cameraView = camera.getView();
	mat4 cameraProjection = camera.getProjection();
	vec3 cameraPosition = camera.getPosition();

	//mat4 mv = cameraView * m_ModelMatrix;
	//program->setUniform("ModelViewMatrix", mv);
	//program->setUniform("NormalMatrix",
		//mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	//program->setUniform("MVP", cameraProjection * mv);
	// Get normal matrix
	//mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
	program->setUniform("M", m_ModelMatrix);
	//prog.setUniform("NormalMatrix", normMat);
	program->setUniform("V", cameraView);
	program->setUniform("P", cameraProjection);
	program->setUniform("cameraPosition", cameraPosition);
}