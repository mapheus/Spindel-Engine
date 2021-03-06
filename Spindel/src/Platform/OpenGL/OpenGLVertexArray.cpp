#include "sppch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Spindel {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Spindel::ShaderDataType::Float: return GL_FLOAT;
		case Spindel::ShaderDataType::Float2: return GL_FLOAT;
		case Spindel::ShaderDataType::Float3: return GL_FLOAT;
		case Spindel::ShaderDataType::Float4: return GL_FLOAT;
		case Spindel::ShaderDataType::Mat3: return GL_FLOAT;
		case Spindel::ShaderDataType::Mat4: return GL_FLOAT;
		case Spindel::ShaderDataType::Int: return GL_INT;
		case Spindel::ShaderDataType::Int2: return GL_INT;
		case Spindel::ShaderDataType::Int3: return GL_INT;
		case Spindel::ShaderDataType::Int4: return GL_INT;
		case Spindel::ShaderDataType::Bool: return GL_BOOL;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffers(const Ref<VertexBuffer>& vertexBuffer)
	{
		SP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}