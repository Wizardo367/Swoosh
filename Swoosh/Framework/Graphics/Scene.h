#pragma once

#include "glslprogram.h"
#include <GLFW/glfw3.h>

#include "Camera.h"
#include <vector>

namespace Swoosh
{
	namespace Framework
	{
		namespace Graphics
		{
			
			class Scene
			{
			protected:
				glm::mat4 m_ModelMatrix;
			public:
				Scene() {}; // Constructor
				// Methods
				virtual void initialise() = 0;
				virtual void render(Camera camera) = 0;
				void linkShaders(GLSLProgram* program, std::vector<const char*> paths);
				virtual void setupLighting(Camera camera) = 0;
				void setCameraMatrices(GLSLProgram* program, Camera camera);
			};

		}
	}
}
