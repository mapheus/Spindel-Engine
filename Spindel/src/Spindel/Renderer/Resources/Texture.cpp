#include "sppch.h"
#include "Spindel/Renderer/Resources/Texture.h"

#include "Spindel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Spindel {

	Ref<Texture2D> Texture2D::Create(const std::string& path, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return Ref<OpenGLTexture2D>::Create(path, name);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(stbi_uc* data, uint32_t width, uint32_t height, uint32_t channels)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return Ref<OpenGLTexture2D>::Create(data, width, height, channels);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}