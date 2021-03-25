#include "sppch.h"
#include "Shader.h"

#include "Spindel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Spindel {
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(path);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}