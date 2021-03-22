#include "sppch.h"
#include "Spindel/Renderer/Texture.h"

#include "Spindel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Spindel {

	Ref<Texture2D> Texture2D::Create(const std::string& path, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path, name);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}