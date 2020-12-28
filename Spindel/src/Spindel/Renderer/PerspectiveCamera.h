#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Spindel {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane);

		inline const glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		inline const glm::quat GetRotation() const { return m_Rotation;  }
		void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjectionMatrix(float fov, float width, float height, float nearPlane, float farPlane);
		void SetViewMatrix(glm::mat4 newMatrix);
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::quat m_Rotation;
	};
}