#include "sppch.h"
#include "PerspectiveCamera.h"

namespace Spindel {
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::perspective(fov, width/height, nearPlane, farPlane)), m_ViewMatrix(1.0f),
		m_Position(0,0,0)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), 0.f, glm::vec3(1, 0, 0));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}