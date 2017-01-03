// Reference: Assignment 2 of IMAT2902-2016-Y

#pragma once

#include <vector>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec2.hpp>

class ObjFile
{
private:
	// ASCII
	static const int forwardSlash = 0x2F;

	// OBJ data
	std::vector<float> m_vertices;					// v
	std::vector<float> m_vertexNormals;				// vn
	std::vector<float> m_vertexTextureCoordinates;	// vt only U V
	// Face data
	std::vector<unsigned int> m_faceVertexIndices;
	std::vector<unsigned int> m_faceTextureIndices;
	std::vector<unsigned int> m_faceNormalIndices;
	// Draw data
	std::vector<float> m_vertexTriplets;	// v
	std::vector<float> m_vertexNormalTriplets;
	std::vector<float> m_vertexTexturePairs;

	// Other data
	std::string m_ModelName;
public:

	ObjFile();
	ObjFile(const char* path);
	~ObjFile();

	bool read(const char* path);

	void processVertexLine(std::istringstream& iss);
	void processVertexNormalLine(std::istringstream& iss);
	void processVertexTextureLine(std::istringstream& iss);
	void processFaceLine(std::istringstream& iss);

	void createExpandedVertices();
	void createExpandedNormals();
	void createExpandedTextureCoordinates();

	std::vector<float> getVertexArray();
	std::vector<float> getUVArray();
	std::vector<float> getNormalArray();
};