#pragma once

#include "gl_core_4_3.hpp"
#include <array>
#include <string>

namespace Swoosh {
	namespace Framework {
		namespace Graphics {

			class Skybox
			{
			private:
				// Variables
				unsigned int m_VaoHandle;
				GLuint m_TexID;
				std::array<float, 72> m_Vertices;
				std::array<unsigned int, 36> m_Indices;
				GLuint m_Vao; // Vertex Array Object
				GLuint m_Iao; // Index Array Object

				unsigned int m_Size;
				std::string m_TextureFilePath;
				std::string m_TexturePrefix;

				// Methods
				void createSkybox();
			public:
				Skybox(std::string textureFilePath, std::string texturePrefix, unsigned int size);  // Constructor
				// Methods
				void render();
				// Functions
				GLuint getTexID();
				~Skybox(); // Destructor
			};

		}
	}
}