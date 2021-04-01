#include "sppch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spindel {
	Ref<VertexArray>  VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexArray>::Create();

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}