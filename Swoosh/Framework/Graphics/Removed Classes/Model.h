#pragma once

#include "../../Framework/Graphics/ObjFile.h"
#include "gl_core_4_3.hpp"

class Model
{
private:
	ObjFile* m_Obj;
	GLuint m_Vao; // Vertex Array Object
	GLuint m_Nao; // Normal Array Object
	GLuint m_Tao; // Texture Array Object
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec2> m_UvCoords;
	std::vector<glm::vec3> m_Normals;
public:
	Model(const char* path);
	~Model();
	// Methods
	void draw(bool includeNormals, bool includeTextures);
	void position(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y ,float z);
};
