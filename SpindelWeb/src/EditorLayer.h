#pragma once
#include "Spindel.h"
#include "imgui/imgui.h"
#include "Panels/SceneHierarchyPanel.h"

#include "Spindel/Renderer/EditorCamera.h"

namespace Spindel {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnImGuiRender() override;

		void OnEvent(Spindel::Event& event) override;

	private:
		PerspectiveFPSCameraController m_Camera;
		EditorCamera m_EditorCamera;

		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = { 0,0 };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		Entity m_TestEntity;
		SceneHierarchyPanel m_SceneHierarchyPanel;

		glm::vec3 squarepos = glm::vec3(20, 0, 0);
		glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), squarepos);
		glm::mat4 pos2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));
	};
}