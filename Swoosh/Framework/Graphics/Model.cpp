// Originally from Assignment 2 of IMAT2902-2016-Y
// File has been modified

#include "Model.h"

#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Bitmap.h"

Model::Model(std::string filename, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	// Initialise variables
	m_Vao = 0;
	m_FileName = filename;
	m_TexturePath = texturePath;

	readModelObjData(filename);

	// Set variables
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;

	// Expand the data suitable for lDrawArrays()
	createExpandedVertices();
	createExpandedNormals();
	createExpandedTextureCoordinates();

	// Buffer data
	buffer();
}

Model::~Model(void)
{
}

void Model::readModelObjData(std::string filename)
{
	std::fstream modelfile(filename, std::ios_base::in);

	if(!modelfile.is_open())
	{
		std::cerr << "File " << filename << " not found.";
		return;	//ERROR!!!
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
			iss >> m_modelName;
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

void Model::processVertexLine(std::istringstream& iss)
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

void Model::processVertexNormalLine(std::istringstream& iss)
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

void Model::processVertexTextureLine(std::istringstream& iss)
{
	// Store 2 floats in m_vertexTextureCoordinates std::vector
	float x, y;

	while (iss >> x >> y)
	{
		m_vertexTextureCoordinates.push_back(x);
		m_vertexTextureCoordinates.push_back(y);
	}
}

void Model::processFaceLine(std::istringstream& iss)
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

void Model::createExpandedVertices()
{
	for (std::vector<unsigned int>::iterator it = m_faceVertexIndices.begin() ; it != m_faceVertexIndices.end(); ++it)
	{
		int vertexNumber = (*it);
		// 3 floats per triangular face
		// Index and copy 3 floats to the m_vertexTriplets std::vector
		for (int i = 0; i < 3; ++i)
			m_vertexTriplets.push_back(m_vertices.at(vertexNumber * 3 + i));
	}
}

void Model::createExpandedNormals()
{
	// we create a list of normal triplets for each face (with duplicates)
	// this will then be the same size as the vertexTriplets std::vector

	for (std::vector<unsigned int>::iterator it = m_faceNormalIndices.begin() ; it != m_faceNormalIndices.end(); ++it)
	{
		// Base index: 1
		// Get the face number indexed at 0
		int vertexNormalNumber = (*it);

		// Index and copy 3 floats to the m_vertexNormalTriplets std::vector
		for (int i = 0; i < 3; ++i)
			m_vertexNormalTriplets.push_back(m_vertexNormals.at(vertexNormalNumber * 3 + i));
	}
}

void Model::createExpandedTextureCoordinates()
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

void Model::buffer()
{
	// Buffer vertex data
	GLuint vbo;
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, m_vertexTriplets.size() * sizeof(float), m_vertexTriplets.data(), gl::STATIC_DRAW);

	// Buffer normal data
	GLuint nbo;
	gl::GenBuffers(1, &nbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, nbo);
	gl::BufferData(gl::ARRAY_BUFFER, m_vertexNormalTriplets.size() * sizeof(float), m_vertexNormalTriplets.data(), gl::STATIC_DRAW);

	// Buffer UV data
	GLuint uvbo;
	gl::GenBuffers(1, &uvbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, uvbo);
	gl::BufferData(gl::ARRAY_BUFFER, m_vertexTexturePairs.size() * sizeof(float), m_vertexTexturePairs.data(), gl::STATIC_DRAW);

	// VAO
	gl::GenVertexArrays(1, &m_Vao);
	gl::BindVertexArray(m_Vao);

	// Vertices
	gl::EnableVertexAttribArray(0);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, nullptr);

	// Normals
	gl::EnableVertexAttribArray(1);
	gl::BindBuffer(gl::ARRAY_BUFFER, nbo);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE_, 0, nullptr);

	// UVs
	gl::EnableVertexAttribArray(2);
	gl::BindBuffer(gl::ARRAY_BUFFER, uvbo);
	gl::VertexAttribPointer(2, 2, gl::FLOAT, gl::FALSE_, 0, nullptr);

	// Texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::GenTextures(1, &m_TexID);
	gl::BindTexture(gl::TEXTURE_2D, m_TexID);

	Bitmap bmp = Bitmap::bitmapFromFile(m_TexturePath);

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, bmp.width(), bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());
	gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
}

void Model::draw()
{
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_TexID);
	gl::BindVertexArray(m_Vao);
	gl::DrawArrays(gl::TRIANGLES, 0, m_vertexTriplets.size());
}

std::string Model::getName()
{
	return m_modelName;
}

glm::vec3 Model::getPosition()
{
	return m_position;
}

glm::vec3 Model::getRotation()
{
	return m_rotation;
}

glm::vec3 Model::getScale()
{
	return m_scale;
}

// Get methods give access to the std::vector data

std::vector<float>& Model::getVertices()
{
	return m_vertexTriplets;
}
std::vector<float>& Model::getNormals()
{
	return m_vertexNormalTriplets;
}
std::vector<float>& Model::getTextureCoordinates()
{
	return m_vertexTexturePairs;
}

GLuint Model::getTexID()
{
	return m_TexID;
}