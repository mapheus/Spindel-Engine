#include "sppch.h"
#include "OpenGLMesh.h"

#include "Spindel/Renderer/Renderer.h"


namespace Spindel
{
	OpenGLMesh::OpenGLMesh()
	{
		float vertices[4 * 5] =
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


		m_Vao = VertexArray::Create();

		m_Vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_Texcoords" }
		};
		m_Vbo->SetLayout(layout);
		m_Vao->AddVertexBuffers(m_Vbo);


		m_Ibo = IndexBuffer::Create(indices, 6);
		m_Vao->AddIndexBuffer(m_Ibo);
		m_Textures.push_back(Texture2D::Create("assets/textures/bomb.png"));

		m_Name = "Default";
	}

	OpenGLMesh::OpenGLMesh(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures)
		: m_Vao(vao), m_Vbo(vbo), m_Ibo(ibo)
	{
		for (auto& i : textures)
			m_Textures.push_back(i);

		m_Name = "Default";
	}
	OpenGLMesh::~OpenGLMesh()
	{

	}
	void OpenGLMesh::Draw(const glm::mat4& transform)
	{
		Renderer::Submit(m_Vao, transform, m_Textures);
	}
}