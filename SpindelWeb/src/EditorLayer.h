#pragma once
#include "Spindel.h"
#include "imgui/imgui.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/AssetPanel.h"

#include "Spindel/Renderer/EditorCamera.h"

#include "Spindel/Scene/Components.h"

#include "Spindel/Assets/Cache.h"

namespace Spindel {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnImGuiRender() override;

		void OnEvent(Spindel::Event& event) override;
		bool OnKeyPressed(KeyPressedEvent& e);

	private:
		EditorCamera m_EditorCamera;

		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = { 0,0 };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		SceneHierarchyPanel m_SceneHierarchyPanel;

		int m_GizmoType = -1;

		glm::vec3 squarepos = glm::vec3(20, 0, 0);
		glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), squarepos);
		glm::mat4 pos2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));
	};
}