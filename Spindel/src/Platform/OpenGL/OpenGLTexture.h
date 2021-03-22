#pragma once

#include "Spindel/Renderer/Texture.h"

#include <glad/glad.h>

namespace Spindel {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, const std::string& name);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		virtual std::string GetName() const override { return m_Name; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		std::string m_Name;

		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}