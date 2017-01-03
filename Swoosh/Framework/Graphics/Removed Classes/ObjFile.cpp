// Reference: Assignment 2 of IMAT2902-2016-Y

#include "ObjFile.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

bool ObjFile::read(const char* path)
{
	std::fstream modelfile(path, std::ios_base::in);

	if (!modelfile.is_open())
	{
		std::cerr << "File " << path << " not found.";
		return false;	//ERROR!!!
	}

	std::string line;
	std::string token = "";
	while (getline(modelfile, line))
	{
		std::istringstream iss(line);

		// process the line
		token = "";

		iss >> token; // read to first whitespace

		if (token == "#")
		{
			// ignore rest of line
			// iss >> s;
		}
		else if (token == "g")
		{
			// read the model name
			iss >> m_ModelName;
			// ignore rest of line
		}
		else if (token == "v")
		{
			processVertexLine(iss);
		}
		else if (token == "vn")
		{
			processVertexNormalLine(iss);
		}
		else if (token == "vt")
		{
			processVertexTextureLine(iss);
		}
		else if (token == "f")
		{
			processFaceLine(iss);
		}
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	modelfile.close();
}

void ObjFile::processVertexLine(std::istringstream& iss)
{
	// Store 3 floats in m_vertices std::vector
	float x, y, z;

	while (iss >> x >> y >> z)
	{
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}
}

void ObjFile::processVertexNormalLine(std::istringstream& iss)
{
	// Store 3 floats in m_vertexNormals std::vector
	float x, y, z;

	while (iss >> x >> y >> z)
	{
		m_vertexNormals.push_back(x);
		m_vertexNormals.push_back(y);
		m_vertexNormals.push_back(z);
	}
}

void ObjFile::processVertexTextureLine(std::istringstream& iss)
{
	// Store 2 floats in m_vertexTextureCoordinates std::vector
	float x, y;

	while (iss >> x >> y)
	{
		m_vertexTextureCoordinates.push_back(x);
		m_vertexTextureCoordinates.push_back(y);
	}
}

void ObjFile::processFaceLine(std::istringstream& iss)
{
	// Process f line data

	/*
	3 formats supported

	v
	v/vt/vn
	v//vn
	*/

	unsigned int vertexIndex, textureIndex, normalIndex;

	for (int i = 0; i < 3; ++i)
	{
		// Get the vertex
		iss >> vertexIndex;
		m_faceVertexIndices.push_back(vertexIndex - 1);

		// Check if the next character is a slash
		if (iss.peek() == forwardSlash)
		{
			// Ignore the slash
			iss.ignore(1);

			// Check if the next character is also a slash, if so then no texture index is given
			if (iss.peek() != forwardSlash)
			{
				// Texture coordinate given
				iss >> textureIndex;
				m_faceTextureIndices.push_back(textureIndex - 1);
			}

			// Ignore slash
			iss.ignore(1);

			// Get the normal index
			iss >> normalIndex;
			m_faceNormalIndices.push_back(normalIndex - 1);
		}
	}
}

void ObjFile::createExpandedVertices()
{
	for (std::vector<unsigned int>::iterator it = m_faceVertexIndices.begin(); it != m_faceVertexIndices.end(); ++it)
	{
		int vertexNumber = (*it);
		// 3 floats per triangular face
		// Index and copy 3 floats to the m_vertexTriplets std::vector
		for (int i = 0; i < 3; ++i)
			m_vertexTriplets.push_back(m_vertices.at(vertexNumber * 3 + i));
	}
}

void ObjFile::createExpandedNormals()
{
	// we create a list of normal triplets for each face (with duplicates)
	// this will then be the same size as the vertexTriplets std::vector

	for (std::vector<unsigned int>::iterator it = m_faceNormalIndices.begin(); it != m_faceNormalIndices.end(); ++it)
	{
		// Base index: 1
		// Get the face number indexed at 0
		int vertexNormalNumber = (*it);

		// Index and copy 3 floats to the m_vertexNormalTriplets std::vector
		for (int i = 0; i < 3; ++i)
			m_vertexNormalTriplets.push_back(m_vertexNormals.at(vertexNormalNumber * 3 + i));
	}
}

void ObjFile::createExpandedTextureCoordinates()
{
	// create actual vertices here (with duplicates)
	// this is in the form that glDrawArrays can work with

	// assume triangles so far
	// assert((faceVertexIndices.size() % 3) == 0);

	for (std::vector<unsigned int>::iterator it = m_faceTextureIndices.begin(); it != m_faceTextureIndices.end(); ++it)
	{
		int textureNumber = (*it);

		// Index and copy 2 floats to the m_vertexTexturePairs std::vector
		for (int i = 0; i < 2; ++i)
			m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(textureNumber * 2 + i));
	}
}

std::vector<float> ObjFile::getVertexArray()
{
	return m_vertexTriplets;
}

std::vector<float> ObjFile::getUVArray()
{
	return m_vertexTexturePairs;
}

std::vector<float> ObjFile::getNormalArray()
{
	return m_vertexNormalTriplets;
}