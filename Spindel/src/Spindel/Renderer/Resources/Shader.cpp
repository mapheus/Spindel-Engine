#include "sppch.h"
#include "Shader.h"

#include "Spindel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Spindel {
	Ref<Shader> Shader::Create(const std::string& source)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLShader>::Create(source);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

}