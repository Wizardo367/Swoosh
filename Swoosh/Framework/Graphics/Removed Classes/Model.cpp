#include "Model.h"
#include <GL/gl.h>
#include "../../Framework/Graphics/gl_core_4_3.hpp"

// Constructor
Model::Model(const char* path)
{
	// Variable initialisation
	m_Obj = new ObjFile(path);

	// Setup model for drawing

	// Get arrays
	m_Vertices = m_Obj->getVertexArray();
	m_UvCoords = m_Obj->getUVArray();
	m_Normals = m_Obj->getNormalArray();

	// Vertex array
	gl::GenVertexArrays(1, &m_Vao);
	gl::BindVertexArray(m_Vao);

	// Buffer vertex data
	GLuint vbo;
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), &m_Vertices, gl::STATIC_DRAW);

	gl::GenVertexArrays(1, &m_Vao);
	gl::BindVertexArray(m_Vao);
	gl::EnableVertexAttribArray(0);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);
}

// Destructor
Model::~Model()
{
	// Clean-up memory
	delete m_Obj;
}

// Methods

void Model::draw(bool includeNormals, bool includeTextures)
{
	gl::BindVertexArray(m_Vao);
	gl::DrawElements(gl::TRIANGLES, m_Vertices.size(), gl::UNSIGNED_INT, nullptr);
}


void Model::position(float x, float y, float z)
{
	
}

void Model::rotate(float x, float y, float z)
{
	
}

void Model::scale(float x, float y, float z)
{
	
}