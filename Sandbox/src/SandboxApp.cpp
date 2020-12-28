#include <Spindel.h>

#include "imgui/imgui.h"


class TestLayer : public Spindel::Layer
{
public:
	TestLayer()	: Layer("Test"), m_Camera(45.f, 1080.f, 720.f, 0.1f, 1000.f)
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

		shader.reset(Spindel::Shader::Create(vsrc, fsrc));
	}

	void OnUpdate() override
	{
		m_Camera.OnUpdate();

		if (Spindel::Input::IsKeyPressed(SP_KEY_E))
			squarepos.y += 0.5;
		if (Spindel::Input::IsKeyPressed(SP_KEY_Q))
			squarepos.y -= 0.5;
		pos1 = glm::translate(glm::mat4(1.0f), squarepos);
	}

	void OnRender() override
	{
		Spindel::Renderer::BeginScene(m_Camera.GetCamera());
		shader->Bind();
		Spindel::Renderer::Submit(shader, vao, pos1);
		Spindel::Renderer::Submit(shader, vao, pos2);
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
		m_Camera.OnEvent(event);
	}


private:
	Spindel::PerspectiveFPSCameraController m_Camera;
	std::shared_ptr<Spindel::VertexArray> vao;
	std::shared_ptr<Spindel::VertexBuffer> vbo;
	std::shared_ptr<Spindel::IndexBuffer> ibo;
	std::shared_ptr<Spindel::Shader> shader;

	glm::vec3 squarepos = glm::vec3(20, 0, 0);
	glm::mat4 pos1 = glm::translate(glm::mat4(1.0f), squarepos);
	glm::mat4 pos2 = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 0, 0));
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