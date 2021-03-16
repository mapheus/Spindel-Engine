#include "Test.h"


TestLayer::TestLayer()
	: Spindel::Layer("Test"), m_Camera(45.f, 1080.f, 720.f, 0.1f, 1000.f)
{

	float vertices[4 * 7] =
	{
		-10.f, -10.f, -20.f, 0.0f, 0.0f, 
		10.f, -10.f, -20.f, 1.0f, 0.0f, 
		10.f, 10.f, -20.f, 1.0f, 1.0f, 
		-10.f, 10.f, -20.f, 0.0f, 1.0f
	};

	unsigned int indices[6] =
	{
		0, 1, 2, 2, 3, 0
	};


	vao = Spindel::VertexArray::Create();

	vbo = Spindel::VertexBuffer::Create(vertices, sizeof(vertices));

	Spindel::BufferLayout layout = {
		{ Spindel::ShaderDataType::Float3, "a_Position" },
		{ Spindel::ShaderDataType::Float2, "a_Texcoords" }
	};
	vbo->SetLayout(layout);
	vao->AddVertexBuffers(vbo);


	ibo = Spindel::IndexBuffer::Create(indices, 6);
	vao->AddIndexBuffer(ibo);

	shader = Spindel::Shader::Create("assets/shaders/Texture.glsl");
	tex = Spindel::Texture2D::Create("assets/textures/bomb.png");

}

void TestLayer::OnUpdate()
{
	m_Camera.OnUpdate();

	if (Spindel::Input::IsKeyPressed(SP_KEY_E))
		squarepos.y += 0.5;
	if (Spindel::Input::IsKeyPressed(SP_KEY_Q))
		squarepos.y -= 0.5;
	pos1 = glm::translate(glm::mat4(1.0f), squarepos);
}

void TestLayer::OnRender()
{
	Spindel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Spindel::RenderCommand::Clear();
	Spindel::Renderer::BeginScene(m_Camera.GetCamera());
	shader->Bind();
	tex->Bind(0);
	Spindel::Renderer::Submit(shader, vao, pos1);
	Spindel::Renderer::Submit(shader, vao, pos2);
	Spindel::Renderer::EndScene();
}

void TestLayer::OnImGuiRender()

{
	ImGui::Begin("Test");
	ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void TestLayer::OnEvent(Spindel::Event& event)
{
	m_Camera.OnEvent(event);
}
