#pragma once
#include "Spindel/Renderer/VertexArray.h"

namespace Spindel {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffers(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual uint32_t GetID() override { return m_RendererID; }

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}