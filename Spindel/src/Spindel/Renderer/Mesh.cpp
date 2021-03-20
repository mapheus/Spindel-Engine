#include "sppch.h"
#include "Mesh.h"

#include "Spindel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLMesh.h"

namespace Spindel {
	Ref<Mesh> Mesh::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLMesh>();

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
	Ref<Mesh> Mesh::Create(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLMesh>(vao, vbo, ibo, textures);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}