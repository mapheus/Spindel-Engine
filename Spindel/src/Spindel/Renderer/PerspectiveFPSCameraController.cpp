#include "sppch.h"
#include "PerspectiveFPSCameraController.h"

#include "Spindel/Core/Input.h"
#include "Spindel/Core/KeyCodes.h"

namespace Spindel {

	PerspectiveFPSCameraController::PerspectiveFPSCameraController(float fov, float width, float height, float nearPlane, float farPlane)
		: m_Fov(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_Camera(fov, width, height, nearPlane, farPlane)
	{

	}

	void PerspectiveFPSCameraController::OnUpdate()
	{
		if (Input::IsKeyPressed(SP_KEY_D))
			m_CameraPosition += m_CameraRight*m_CameraTranslationSpeed;
		if (Input::IsKeyPressed(SP_KEY_A))
			m_CameraPosition -= m_CameraRight * m_CameraTranslationSpeed;
		if (Input::IsKeyPressed(SP_KEY_W))
			m_CameraPosition += m_CameraFront*m_CameraTranslationSpeed;
		if (Input::IsKeyPressed(SP_KEY_S))
			m_CameraPosition -= m_CameraFront*m_CameraTranslationSpeed;
			
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetViewMatrix(GetViewMatrix());
	}
	void PerspectiveFPSCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_EVENT_FN(PerspectiveFPSCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(SP_BIND_EVENT_FN(PerspectiveFPSCameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(SP_BIND_EVENT_FN(PerspectiveFPSCameraController::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(SP_BIND_EVENT_FN(PerspectiveFPSCameraController::OnMouseReleased));
	}

	void PerspectiveFPSCameraController::OnResize(float width, float height)
	{
		m_Camera.SetProjectionMatrix(m_Fov, width, height, m_NearPlane, m_FarPlane);
	}
	bool PerspectiveFPSCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize(e.GetWidth(), e.GetHeight());
		return false;
	}
	bool PerspectiveFPSCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (m_MouseEnabled)
		{
			if (m_FirstMouseMove)
			{
				m_LastX = e.GetX();
				m_LastY = e.GetY();
				m_FirstMouseMove = false;
			}
			m_Yaw += (e.GetX() - m_LastX) * m_CameraRotateSpeed;
			m_Pitch -= (e.GetY() - m_LastY) * m_CameraRotateSpeed;

			if (true)
			{
				if (m_Pitch > 89.0f)
					m_Pitch = 89.0f;
				if (m_Pitch < -89.0f)
					m_Pitch = -89.0f;
			}

			m_LastX = e.GetX();
			m_LastY = e.GetY();
			UpdateCameraVectors();
		}
		return false;
	}
	bool PerspectiveFPSCameraController::OnMousePressed(MouseButtonPressedEvent& e)
	{
		m_MouseEnabled = true;
		return false;
	}
	bool PerspectiveFPSCameraController::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		m_FirstMouseMove = true;
		m_MouseEnabled = false;
		return false;
	}
	void PerspectiveFPSCameraController::UpdateCameraVectors()
	{
		m_CameraFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront.y = sin(glm::radians(m_Pitch));
		m_CameraFront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(m_CameraFront);
		// also re-calculate the Right and Up vector
		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, glm::vec3(0,1,0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
		m_Camera.SetViewMatrix(GetViewMatrix());
	}
}