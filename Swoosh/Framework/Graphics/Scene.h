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
			public:
				Scene() {}; // Constructor
				// Methods
				virtual void initialise() = 0;
				virtual void render(Camera camera) = 0;
				void linkShaders(GLSLProgram* program, std::vector<const char*> paths);
			};

		}
	}
}
