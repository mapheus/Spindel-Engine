#pragma once

#include <string>
#include "Spindel/Renderer/Shader.h"

namespace Spindel {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		uint32_t m_RendererID;
	};
}