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