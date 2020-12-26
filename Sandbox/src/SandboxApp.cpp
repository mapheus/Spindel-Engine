#include <Spindel.h>

#include "imgui/imgui.h"


class TestLayer : public Spindel::Layer
{
public:
	TestLayer()	: Layer("Test"), m_Camera(90.f, 1080.f, 720.f, 0.1f, 1000.f)
	{

		float vertices[4 * 7] =
		{
			-10.5f, -0.5f, -20.f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -10.5f, -20.f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -20.f, 0.0f, 0.0f, 1.0f, 1.0f,
			-10.5f, 20.5f, -20.f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 2, 2, 3, 0
		};


		vao.reset(Spindel::VertexArray::Create());

		vbo.reset(Spindel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Spindel::BufferLayout layout = {
			{ Spindel::ShaderDataType::Float3, "a_Position" },
			{ Spindel::ShaderDataType::Float4, "a_Color" }
		};
		vbo->SetLayout(layout);
		vao->AddVertexBuffers(vbo);


		ibo.reset(Spindel::IndexBuffer::Create(indices, 6));
		vao->AddIndexBuffer(ibo);

		std::string vsrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;
			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1);
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

		shader.reset(Spindel::Shader::Create(vsrc, fsrc));
	}

	void OnUpdate() override
	{
		if (Spindel::Input::IsKeyPressed(SP_KEY_D))
			m_Camera.SetPosition(glm::vec3(m_Camera.GetPosition().x + 0.1f, m_Camera.GetPosition().y, m_Camera.GetPosition().z));

		if (Spindel::Input::IsKeyPressed(SP_KEY_A))
			m_Camera.SetPosition(glm::vec3(m_Camera.GetPosition().x - 0.1f, m_Camera.GetPosition().y, m_Camera.GetPosition().z));

		if (Spindel::Input::IsKeyPressed(SP_KEY_W))
			m_Camera.SetPosition(glm::vec3(m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z -0.1f));

		if (Spindel::Input::IsKeyPressed(SP_KEY_S))
			m_Camera.SetPosition(glm::vec3(m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z + 0.1f));

		Spindel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Spindel::RenderCommand::Clear();

		Spindel::Renderer::BeginScene(m_Camera);
		shader->Bind();
		Spindel::Renderer::Submit(shader, vao);
		Spindel::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void OnEvent(Spindel::Event& event) override
	{
	}


private:
	Spindel::PerspectiveCamera m_Camera;
	std::shared_ptr<Spindel::VertexArray> vao;
	std::shared_ptr<Spindel::VertexBuffer> vbo;
	std::shared_ptr<Spindel::IndexBuffer> ibo;
	std::shared_ptr<Spindel::Shader> shader;
};


class Sandbox : public Spindel::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	~Sandbox()
	{

	}
};

Spindel::Application* Spindel::CreateApplication()
{
	return new Sandbox();
}