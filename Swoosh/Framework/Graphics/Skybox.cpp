#include "Skybox.h"
#include "Bitmap.h"

namespace Swoosh {
	namespace Framework {
		namespace Graphics {

			// Constructor
			Skybox::Skybox(std::string textureFilePath, std::string texturePrefix, unsigned int size)
			{
				// Variable initialisation
				m_TextureFilePath = textureFilePath;
				m_TexturePrefix = texturePrefix;
				m_Size = size;
				// Initialisation
				createSkybox();
			}

			// Destructor
			Skybox::~Skybox()
			{
			}

			// Methods

			void Skybox::createSkybox()
			{
				// Vertex array
				gl::GenVertexArrays(1, &m_Vao);
				gl::BindVertexArray(m_Vao);

				// Vertices
				m_Vertices =
				{
					// Front
					-1.0, -1.0,  1.0,
					 1.0, -1.0,  1.0,
					 1.0,  1.0,  1.0,
					-1.0,  1.0,  1.0,
					// Right
					 1.0,  1.0,  1.0,
					 1.0,  1.0, -1.0,
					 1.0, -1.0, -1.0,
					 1.0, -1.0,  1.0,
					// Back
					-1.0, -1.0, -1.0,
					 1.0, -1.0, -1.0,
					 1.0,  1.0, -1.0,
					-1.0,  1.0, -1.0,
					// Left
					-1.0, -1.0, -1.0,
					-1.0, -1.0,  1.0,
					-1.0,  1.0,  1.0,
					-1.0,  1.0, -1.0,
					// Upper
					 1.0,  1.0,  1.0,
					-1.0,  1.0,  1.0,
					-1.0,  1.0, -1.0,
					 1.0,  1.0, -1.0,
				    // Bottom
					-1.0, -1.0, -1.0,
				     1.0, -1.0, -1.0,
					 1.0, -1.0,  1.0,
					-1.0, -1.0,  1.0
				};

				// Indices
				m_Indices =
				{
					0,  1,  2,  0,  2,  3,   // Front
					4,  5,  6,  4,  6,  7,   // Right
					8,  9,  10, 8,  10, 11,  // Back
					12, 13, 14, 12, 14, 15,  // Left
					16, 17, 18, 16, 18, 19,  // Upper
					20, 21, 22, 20, 22, 23   // Bottom
				};

				// Adjust size of cube
				for (float &vertex : m_Vertices)
					vertex *= m_Size;

				// Buffer vertex data
				GLuint vbo;
				gl::GenBuffers(1, &vbo);
				gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
				gl::BufferData(gl::ARRAY_BUFFER, m_Vertices.size() * sizeof(float), &m_Vertices[0], gl::STATIC_DRAW);

				// Buffer index data
				GLuint ibo;
				gl::GenBuffers(1, &ibo);
				gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo);
				gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], gl::STATIC_DRAW);

				// Bind Arrays
				gl::EnableVertexAttribArray(0);
				gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, nullptr);
				gl::BindVertexArray(0);

				// Texture
				gl::ActiveTexture(gl::TEXTURE0);

				gl::GenTextures(1, &m_TexID);
				gl::BindTexture(gl::TEXTURE_CUBE_MAP, m_TexID);

				std::array<std::string, 6> suffixes = { "r", "l", "u", "d", "f", "b" };

				// Load the images
				for (int i = 0; i < 6; i++)
				{
					std::string textureFile = m_TextureFilePath + m_TexturePrefix + suffixes[i] + ".jpg";
					Bitmap bmp = Bitmap::bitmapFromFile(textureFile);
					gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, gl::RGB, bmp.width(), bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());
				}

				gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
				gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
				gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
				gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
				gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);
			}

			void Skybox::render()
			{
				gl::DepthMask(gl::FALSE_);
				gl::ActiveTexture(gl::TEXTURE0);
				gl::BindTexture(gl::TEXTURE_CUBE_MAP, m_TexID);
				gl::BindVertexArray(m_Vao);
				gl::DrawElements(gl::TRIANGLES, m_Indices.size(), gl::UNSIGNED_INT, 0);
				gl::DepthMask(gl::TRUE_);
			}

			GLuint Skybox::getTexID()
			{
				return m_TexID;
			}

		}
	}
}