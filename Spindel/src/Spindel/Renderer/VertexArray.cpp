#include "sppch.h"
#include "VertexArray.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spindel {
	Ref<VertexArray>  VertexArray::Create()
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLVertexArray>::Create();

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}