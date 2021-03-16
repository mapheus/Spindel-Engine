#pragma once
#include "Spindel.h"
#include "imgui/imgui.h"

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
		Ref<Framebuffer> m_Framebuffer;
		Ref<VertexArray> vao;
		Ref<VertexBuffer> vbo;
		Ref<IndexBuffer> ibo;
		Ref<Shader> shader;
		Ref<Texture2D> tex;
		glm::vec2 m_ViewportSize = { 0,0 };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec3 squarepos = glm::vec3(20, 0, 0);
		glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), squarepos);
		glm::mat4 pos2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));
	};
}