#include "sppch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Spindel {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return new OpenGLShader(vertexSrc, fragmentSrc);
	}
}