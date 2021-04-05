#include "sppch.h"
#include "Spindel/Renderer/Framebuffer.h"

#include "Spindel/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Spindel {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPIType::OpenGL:  return Ref<OpenGLFramebuffer>::Create(spec);
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}