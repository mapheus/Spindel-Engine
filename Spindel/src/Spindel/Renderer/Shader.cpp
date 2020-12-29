#include "sppch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Spindel {
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
	}
}