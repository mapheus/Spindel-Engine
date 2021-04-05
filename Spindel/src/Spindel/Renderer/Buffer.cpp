#include "sppch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"
namespace Spindel {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(vertices, size);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(std::vector<Vertex> vertices, size_t size)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLVertexBuffer>::Create (vertices, size);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices, count);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(std::vector<uint32_t> indices)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPIType::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}