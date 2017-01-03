#pragma once
#include "glslprogram.h"
#include <iostream>
#include <vector>

// Static class

namespace Swoosh
{
	namespace Framework
	{
		namespace Graphics
		{

			class Shader
			{
			public:
				// Compile and link shader
				static void attachShaders(GLSLProgram* program, std::vector<const char*> paths)
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
			};

		}
	}
}