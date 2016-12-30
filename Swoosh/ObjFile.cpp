// Reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include "ObjFile.h"
#include <iostream>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>

// Constructor
ObjFile::ObjFile()
{
}

// Overridden Constructor
ObjFile::ObjFile(const char* path)
{
	read(path);
}


// Destructor
ObjFile::~ObjFile()
{
}

// Load model
bool ObjFile::read(const char* path)
{
	// Temp variables for parsing data
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_verts;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	// Load file
	FILE* file;
	errno_t fileError = fopen_s(&file, path, "r");
	if (fileError != 0) {
		std::cerr << "Error: File loading failed!" << "\n";
		return false;
	}

	// Read file
	while (true)
	{
		char lineHeader[1024]; // Assumes lineheader isn't longer than 1024 characters
		// Read first word of line
		int fWord = fscanf_s(file, "%s", lineHeader);
		if (fWord == EOF)
			break; // End of file reached

		// Parse data

		if (strcmp(lineHeader, "v") == 0) {
			// Vertices
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_verts.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			// UVs
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			// Normals
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			// Faces
			std::string vert1, vert2, vert3;
			unsigned int vertIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertIndex[0], &uvIndex[0], &normalIndex[0], &vertIndex[1], &uvIndex[1], &normalIndex[1], &vertIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::cerr << "Error: file is too complex, try exporting with other options!" << "\n";
				return false;
			}

			vertexIndices.push_back(vertIndex[0]);
			vertexIndices.push_back(vertIndex[1]);
			vertexIndices.push_back(vertIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

		// Process data

		// Vertices
		for (unsigned int i = 0 ; i < vertexIndices.size(); i++)
		{
			unsigned int index = vertexIndices[i];
			// Change index to make array 0-based
			glm::vec3 vertex = temp_verts[index - 1];
			// Push to array
			m_vertices.push_back(vertex);
		}

		// UVs
		for (unsigned int i = 0; i < uvIndices.size(); i++)
		{
			unsigned int index = uvIndices[i];
			// Change index to make array 0-based
			glm::vec2 uv = temp_uvs[index - 1];
			// Push to array
			m_textureCoords.push_back(uv);
		}

		// Normals
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int index = normalIndices[i];
			// Change index to make array 0-based
			glm::vec3 normal = temp_normals[index - 1];
			// Push to array
			m_vertexNormals.push_back(normal);
		}
	}
}