#include "sppch.h"
#include "MeshManager.h"

#include "Spindel/Core/Core.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Buffer.h"
#include "Spindel/Renderer/Texture.h"

namespace Spindel
{

	static std::vector<Ref<Mesh>> m_Meshes;
	static std::vector<Ref<Model>> m_Models;

	void MeshManager::Init()
	{
	}

	Ref<Mesh> MeshManager::CreateMesh(const std::string& name)
	{
		Ref<Mesh> m = Mesh::Create(name);
		m_Meshes.push_back(m);
		return m;
	}
	Ref<Mesh> MeshManager::CreateMesh(const std::string& name, Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures)
	{
		Ref<Mesh> m = Mesh::Create(name, vao, vbo, ibo, textures);
		m_Meshes.push_back(m);
		return m;
	}
	Ref<Model> MeshManager::CreateModel(const std::string& path)
	{
		Ref<Model> m = CreateRef<Model>(path);
		m_Models.push_back(m);
		return m;
	}
	Ref<Mesh> MeshManager::CreateCube(const std::string& name)
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

		unsigned int indices[6 * 6] =
		{
			0, 1, 2, 2, 3, 0,
			0, 1, 4, 1, 5, 4,
			1, 5, 2, 5, 6, 2,
			3, 2, 7, 2, 6, 7,
			4, 0, 7, 0, 3, 7,
			5, 4, 6, 4, 7, 6
		};


		Ref<VertexArray> vao = VertexArray::Create();

		Ref<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_Texcoords" }
		};
		vbo->SetLayout(layout);
		vao->AddVertexBuffers(vbo);


		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, 36);
		vao->AddIndexBuffer(ibo);
		std::vector<Ref<Texture2D>> textures;
		textures.push_back(Texture2D::Create("assets/textures/mgsus.png"));
		Ref<Mesh> m = Mesh::Create(name, vao, vbo, ibo, textures);
		m_Meshes.push_back(m);
		return m;
	}
	Ref<Mesh> MeshManager::CreatePlane(const std::string& name)
	{
		float vertices[8 * 5] =
		{
		-10.f, 0.f, 10.f, 0.0f, 0.0f,
		10.f, 0.f, 10.f, 1.0f, 0.0f,
		10.f, 0.f, -10.f, 1.0f, 1.0f,
		-10.f, 0.f, -10.f, 0.0f, 1.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 2, 2, 3, 0
		};


		Ref<VertexArray> vao = VertexArray::Create();

		Ref<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_Texcoords" }
		};
		vbo->SetLayout(layout);
		vao->AddVertexBuffers(vbo);


		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, 36);
		vao->AddIndexBuffer(ibo);
		std::vector<Ref<Texture2D>> textures;
		textures.push_back(Texture2D::Create("assets/textures/mgsus.png"));
		Ref<Mesh> m = Mesh::Create(name, vao, vbo, ibo, textures);
		m_Meshes.push_back(m);
		return m;
	}
	Ref<Mesh> MeshManager::GetMesh(const std::string& name)
	{
		for (auto& i : m_Meshes)
		{
			if (i->GetName() == name)
				return i;
		}
		return nullptr;
	}
	Ref<Model> MeshManager::GetModel(const std::string& name)
	{
		for (auto& i : m_Models)
		{
			if (i->GetName() == name)
				return i;
		}
		return nullptr;
	}
	std::vector<Ref<Mesh>> MeshManager::GetAllMeshes()
	{
		return m_Meshes;
	}

	std::vector<Ref<Model>> MeshManager::GetAllModels()
	{
		return m_Models;
	}


}