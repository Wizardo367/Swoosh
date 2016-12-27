// QuatCamera from Assignment 1 of IMAT-3111-Y used as reference

#include "Camera.h"

// Constructor
Camera::Camera()
{
	reset();
}

// Destructor
Camera::~Camera()
{
}

// Reset
void Camera::reset()
{
	// Reset axes
	m_XAxis = m_WorldXAxis;
	m_YAxis = m_WorldYAxis;
	m_ZAxis = m_WorldZAxis;

	// Reset position
	m_Position = glm::vec3(0.f, 0.f, 0.f);
	// Reset orientation
	m_Orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	// Reset properties
	m_FieldOfView = glm::radians(50.0f);
	m_NearPlane = 0.01f;
	m_FarPlane = 100.0f;
	m_AspectRatio = 16.f / 9.f;

	// Reset projection
	m_Projection = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearPlane, m_FarPlane);
	// Update view
	updateView();
}

glm::quat Camera::generateQuaternion(glm::vec3 axis, float angle)
{
	glm::quat quaternion;

	const float halfAngle = angle / 2.f;
	const float cosine = std::cos(halfAngle);
	const float sine = std::sin(halfAngle);

	quaternion = glm::quat(cosine, sine * axis.x, sine * axis.y, sine * axis.z);

	return quaternion;
}

// Rotate
void Camera::rotate(const float yaw, const float pitch)
{
	m_Orientation = glm::normalize(generateQuaternion(m_WorldXAxis, pitch) * m_Orientation); // Rotate pitch (X axis)
	m_Orientation = glm::normalize(m_Orientation * generateQuaternion(m_WorldYAxis, yaw)); // Rotate yaw (Y axis)
	updateView();
}

// Pan
void Camera::pan(const float x, const float y)
{
	// Offset position
	m_Position += m_XAxis * x;
	m_Position += m_YAxis * y;
	updateView();
}

// Zoom
void Camera::zoom(const float z)
{
	m_Position -= m_ZAxis * z;
	updateView();
}

// Update view
void Camera::updateView()
{
	// Convert quaternion to 4x4 matrix
	m_View = glm::mat4_cast(m_Orientation);

	// Get camera axes from matrix
	m_XAxis = glm::vec3(m_View[0][0], m_View[1][0], m_View[2][0]);
	m_YAxis = glm::vec3(m_View[0][1], m_View[1][1], m_View[2][1]);
	m_ZAxis = glm::vec3(m_View[0][2], m_View[1][2], m_View[2][2]);

	// Combine with current camera position to translate view
	m_View[3][0] = -glm::dot(m_XAxis, m_Position);
	m_View[3][1] = -glm::dot(m_YAxis, m_Position);
	m_View[3][2] = -glm::dot(m_ZAxis, m_Position);
}