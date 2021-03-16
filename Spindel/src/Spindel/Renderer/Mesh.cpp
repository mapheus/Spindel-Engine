#include "sppch.h"
#include "Mesh.h"

#include "Spindel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLMesh.h"
#include "Spindel/Renderer/Texture.h"

namespace Spindel {
	Ref<Mesh> Mesh::Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<class Texture*>& textures)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLMesh>(vertices, indices, textures);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}