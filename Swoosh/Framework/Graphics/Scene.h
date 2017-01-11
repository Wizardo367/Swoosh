#pragma once

#include "glslprogram.h"
#include <GLFW/glfw3.h>

#include "camera.h"
#include <vector>
#include "../Input/Mouse.h"

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
				Input::Mouse m_Mouse;
				GLFWwindow* m_Window;
				float m_RotationVelocity;
				float m_MoveVelocity;
			public:
				Scene(GLFWwindow* window); // Constructor
				// Methods
				virtual void initialise() = 0;
				virtual void render(Camera* camera) = 0;
				virtual void setupLighting(GLSLProgram* program, Camera* camera) = 0;
				void setCameraMatrices(GLSLProgram* program, Camera* camera);
				virtual void update(Camera* camera, float deltaTime);
			};

		}
	}
}
