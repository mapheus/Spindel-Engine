#pragma once

#include "Spindel/Renderer/Buffer.h"
#include <memory>

namespace Spindel {
	class VertexArray : public RefCounted
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffers(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual uint32_t GetID() = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

}