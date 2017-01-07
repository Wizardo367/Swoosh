#include "Scene.h"
#include <iostream>
#include "../Input/Mouse.h"

// Constructor
Swoosh::Framework::Graphics::Scene::Scene(GLFWwindow* window)
{
	m_Window = window;
	m_Mouse = m_Mouse.getInstance(window);
	m_MoveVelocity = 1.25f;
	m_RotationVelocity = 0.05f;
}

// Camera matrices setup
void Swoosh::Framework::Graphics::Scene::setCameraMatrices(GLSLProgram* program, Camera* camera)
{
	mat4 cameraView = camera->getView();
	mat4 cameraProjection = camera->getProjection();
	vec3 cameraPosition = camera->getPosition();

	//mat4 mv = cameraView * m_ModelMatrix;
	//program->setUniform("ModelViewMatrix", mv);
	//program->setUniform("NormalMatrix",
		//mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	//program->setUniform("MVP", cameraProjection * mv);
	// Get normal matrix
	//mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
	program->setUniform("M", m_ModelMatrix);
	//prog.setUniform("NormalMatrix", normMat);
	program->setUniform("V", cameraView);
	program->setUniform("P", cameraProjection);
	program->setUniform("cameraPosition", cameraPosition);
}

void Swoosh::Framework::Graphics::Scene::update(Camera* camera, float deltaTime)
{
	// Get delta mouse position
	glm::vec2 mouseMovement = m_Mouse.getDeltaMousePosition();

	// Check button clicks
	
	// Rotate camera
	if (m_Mouse.wasButtonClicked(GLFW_MOUSE_BUTTON_LEFT))
	{
		float rotation = m_RotationVelocity * deltaTime;
		camera->rotate(mouseMovement.x * rotation, mouseMovement.y * rotation);
	}

	// Move camera
	if (m_Mouse.wasButtonClicked(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float pan = m_MoveVelocity * deltaTime;
		camera->pan(mouseMovement.x * pan, mouseMovement.y * pan);
	}
}