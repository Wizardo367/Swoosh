#pragma once
#include <vector>
#include <glm/detail/type_vec3.hpp>

class ObjFile
{
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<glm::vec3> m_vertexNormals;
public:
	ObjFile();
	ObjFile(const char* path);
	~ObjFile();
	bool read(const char* path);
};
