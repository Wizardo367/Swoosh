// Originally from Assignment 2 of IMAT2902-2016-Y
// File has been modified

#pragma once

//#include "TextureLoader.h"
#include "gl_core_4_3.hpp"

#include <string>
#include <vector>
#include <glm/detail/type_vec3.hpp>
#include <glm/mat4x4.hpp>

class Model
{
	private:
		// need to know ascii for forward slash
		static const int forwardSlash = 0x2F;

		//
		// this is the data read from the OBJ file....
		//

		std::vector<float> m_vertices;					// v
		std::vector<float> m_vertexNormals;				// vn
		std::vector<float> m_vertexTextureCoordinates;	// vt only U V

		// character buffers for the raw textures
		// char textureData1[256*256*3];
		// char textureData2[256*256*3];
		// array of OpenGL texture objects 
		//GLuint m_textureID[2];

		// f   v/vt/vn  (vt and vn optional)
		// these are unsigned as opengl expected unsigned data
		std::vector<unsigned int> m_faceVertexIndices;
		std::vector<unsigned int> m_faceTextureIndices;
		std::vector<unsigned int> m_faceNormalIndices;   

		std::string m_modelName;
		glm::vec3 m_position, m_rotation, m_scale;

		// because maya output indices that don't necessarily match for
		// faces normals and textures we have two options
		// 1. rebalance the texture and normal indices to match the face indices - then draw with glDrawElements
		// 2. Create buffers with duplicated vertices, texture coordinates and normals and use glDrawArrays
		//
		// 1 is probably more efficient but 2 is perhaps a little clearer...

		// to simply test we generate a set of vertex triplets that repeat vertices
		// but which ww can simply pass to open gl in sequence to draw each triangle
		// in the model

		std::vector<float> m_vertexTriplets;	// v
		std::vector<float> m_vertexNormalTriplets; 
		std::vector<float> m_vertexTexturePairs;

		GLuint m_Vao; // Vertex Array Object
		GLuint m_TexID; // Texture ID

		std::string m_FileName, m_TexturePath;
	public:
		Model(std::string filename, std::string texturePath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		~Model(void);

		void Model::readModelObjData(std::string filename);

		void processVertexLine(std::istringstream& iss);
		void processVertexNormalLine(std::istringstream& iss);
		void processVertexTextureLine(std::istringstream& iss);
		void processFaceLine(std::istringstream& iss);

		void createExpandedVertices();
		void createExpandedNormals();
		void createExpandedTextureCoordinates();

		void buffer();
		void draw();

		std::string getName();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		std::vector<float>& getVertices();
		std::vector<float>& getNormals();
		std::vector<float>& getTextureCoordinates();

		GLuint getTexID();
};

