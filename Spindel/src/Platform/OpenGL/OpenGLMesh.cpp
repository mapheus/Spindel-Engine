#include "sppch.h"
#include "OpenGLMesh.h"

#include "Spindel/Renderer/Renderer.h"


namespace Spindel
{
	OpenGLMesh::OpenGLMesh(const std::string& name)
	{
		float vertices[8 * 5] =
		{
		-10.f, -10.f, -10.f, 0.0f, 0.0f,
		10.f, -10.f, -10.f, 1.0f, 0.0f,
		10.f, 10.f, -10.f, 1.0f, 1.0f,
		-10.f, 10.f, -10.f, 0.0f, 1.0f,
		-10.f, -10.f, 10.f, 0.0f, 0.0f,
		10.f, -10.f, 10.f, 1.0f, 0.0f,
		10.f, 10.f, 10.f, 1.0f, 1.0f,
		-10.f, 10.f, 10.f, 0.0f, 1.0f
		};

		unsigned int indices[6*6] =
		{
			0, 1, 2, 2, 3, 0,
			0, 1, 4, 1, 5, 4,
			1, 5, 2, 5, 6, 2,
			3, 2, 7, 2, 6, 7,
			4, 0, 7, 0, 3, 7,
			5, 4, 6, 4, 7, 6
		};


		m_Vao = VertexArray::Create();

		m_Vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_Texcoords" }
		};
		m_Vbo->SetLayout(layout);
		m_Vao->AddVertexBuffers(m_Vbo);


		m_Ibo = IndexBuffer::Create(indices, 36);
		m_Vao->AddIndexBuffer(m_Ibo);
		m_Textures.push_back(Texture2D::Create("assets/textures/mgsus.png"));

		m_Name = name;
	}

	OpenGLMesh::OpenGLMesh(const std::string& name, Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures)
		: m_Vao(vao), m_Vbo(vbo), m_Ibo(ibo)
	{
		for (auto& i : textures)
		{
			m_Textures.push_back(i);
		}

		m_Name = name;
	}
	OpenGLMesh::~OpenGLMesh()
	{

	}

	void OpenGLMesh::Draw(const glm::mat4& transform)
	{
		Renderer::Submit(m_Vao, transform, m_Textures);
	}
}