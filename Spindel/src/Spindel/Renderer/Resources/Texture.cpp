#include "sppch.h"
#include "Spindel/Renderer/Resources/Texture.h"

#include "Spindel/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Spindel {

	Ref<Texture2D> Texture2D::Create(stbi_uc* data, uint32_t width, uint32_t height, uint32_t channels)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPIType::OpenGL:  return Ref<OpenGLTexture2D>::Create(data, width, height, channels);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	uint32_t Texture::GetBPP(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB:    return 3;
		case TextureFormat::RGBA:   return 4;
		}
		return 0;
	}

	uint32_t Texture::CalculateMipMapCount(uint32_t width, uint32_t height)
	{
		uint32_t levels = 1;
		while ((width | height) >> levels)
			levels++;

		return levels;
	}

}