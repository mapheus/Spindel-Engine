#include "sppch.h"
#include "Mesh.h"

#include "Spindel/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLMesh.h"

namespace Spindel {
	Ref<Mesh> Mesh::Create(const std::string& name)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLMesh>::Create(name);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
	Ref<Mesh> Mesh::Create(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLMesh>::Create(vao, vbo, ibo, textures);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

}