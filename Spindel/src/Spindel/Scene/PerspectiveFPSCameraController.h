#pragma once
#include "Spindel/Scene/PerspectiveCamera.h"

#include "Spindel/Events/ApplicationEvent.h"
#include "Spindel/Events/MouseEvent.h"

namespace Spindel {

	class PerspectiveFPSCameraController
	{
	public:
		PerspectiveFPSCameraController(float fov, float width, float height, float nearPlane, float farPlane);
	
		void OnUpdate();
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		glm::mat4 GetViewMatrix() { return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp); }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);
		bool OnMouseReleased(MouseButtonReleasedEvent& e);
	private:
		void UpdateCameraVectors();
	private:
		PerspectiveCamera m_Camera;
		float m_Fov = 45.f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.f;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraFront = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_CameraUp = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_CameraRight = { 1.0f, 0.0f, 0.0f };

		bool m_MouseEnabled = false;
		bool m_FirstMouseMove = true;
		float m_LastX = 0;
		float m_LastY = 0;

		float m_Yaw = -90.f;
		float m_Pitch = 0.f;
		float m_CameraTranslationSpeed = 0.5f;
		float m_CameraRotateSpeed = 0.2f;
	};
}