// QuatCamera from Assignment 1 of IMAT-3111-Y used as reference

#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"

class Camera
{
private:
	// Properties
	const char* m_ID;

	float m_FieldOfView;
	float m_NearPlane, m_FarPlane;
	float m_AspectRatio;

	// Axes
	glm::vec3 m_XAxis;
	glm::vec3 m_YAxis;
	glm::vec3 m_ZAxis;

	// Position, Rotation and View
	glm::vec3 m_Position;
	glm::quat m_Orientation;
	glm::mat4 m_View;
	glm::mat4 m_Projection;

	// Generate quaternion from axis and rotation angle in radians
	glm::quat generateQuaternion(glm::vec3 axis, float angle);

	// World axes
	const glm::vec3 m_WorldXAxis;
	const glm::vec3 m_WorldYAxis;
	const glm::vec3 m_WorldZAxis;

	// Lock
	bool m_Locked = false;
public:
	Camera(const char* id); // Constructor
	~Camera(); // Destructor

	// Properties
	const char* getID();

	float getFieldOfView();
	void setFieldOfView(float fov);
	float getAspectRatio();
	void setAspectRatio(float ratio);
	float getNearPlane();
	float getFarPlane();
	void setPlanes(float nearPlane, float farPlane);

	glm::mat4 getView();
	glm::mat4 getProjection();

	// Position, Rotation and Zoom
	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);

	void lock(bool lock);

	virtual void rotate(const float yaw, const float pitch);
	virtual void pan(const float x, const float y);
	virtual void zoom(const float z);

	// Other functionality
	virtual void updateView();
	virtual void reset();
};

