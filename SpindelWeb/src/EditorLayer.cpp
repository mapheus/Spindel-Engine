#include "EditorLayer.h"

namespace Spindel {


	EditorLayer::EditorLayer()
		: Layer("Test"), m_Camera(45.f, 1080.f, 720.f, 0.1f, 1000.f)
	{
		float vertices[4 * 7] =
		{
			-10.f, -10.f, -20.f, 1.0f, 0.0f, 0.0f, 1.0f,
			10.f, -10.f, -20.f, 0.0f, 1.0f, 0.0f, 1.0f,
			10.f, 10.f, -20.f, 0.0f, 0.0f, 1.0f, 1.0f,
			-10.f, 10.f, -20.f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 2, 2, 3, 0
		};


		vao = Spindel::VertexArray::Create();

		vbo = Spindel::VertexBuffer::Create(vertices, sizeof(vertices));

		Spindel::BufferLayout layout = {
			{ Spindel::ShaderDataType::Float3, "a_Position" },
			{ Spindel::ShaderDataType::Float4, "a_Color" }
		};
		vbo->SetLayout(layout);
		vao->AddVertexBuffers(vbo);


		ibo = Spindel::IndexBuffer::Create(indices, 6);
		vao->AddIndexBuffer(ibo);

		std::string vsrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;
			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1);
			}
			)";

		std::string fsrc = R"(
			#version 330 core
			out vec4 f_Color;
			
			in vec4 v_Color;
			void main()
			{
				f_Color = v_Color;
			}
			)";

		shader = Spindel::Shader::Create(vsrc, fsrc);
	}

	void EditorLayer::OnAttach()
	{
		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnUpdate()
	{
		m_Camera.OnUpdate();

		if (Spindel::Input::IsKeyPressed(SP_KEY_E))
			squarepos.y += 0.5;
		if (Spindel::Input::IsKeyPressed(SP_KEY_Q))
			squarepos.y -= 0.5;
		pos1 = glm::translate(glm::mat4(1.0f), squarepos);

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_Camera.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}
		
	}

	void EditorLayer::OnRender()
	{
		m_Framebuffer->Bind();
		Spindel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Spindel::RenderCommand::Clear();
		
		Spindel::Renderer::BeginScene(m_Camera.GetCamera());
		shader->Bind();
		Spindel::Renderer::Submit(shader, vao, pos1);
		Spindel::Renderer::Submit(shader, vao, pos2);
		Spindel::Renderer::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;



		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
		

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		
		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Test");
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Spindel::Event& event)
	{
		m_Camera.OnEvent(event);
	}

}