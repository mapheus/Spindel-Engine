#include "sppch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
namespace Spindel {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(vertices, size);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(std::vector<Vertex> vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create (vertices, size);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices, count);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(std::vector<uint32_t> indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI::None is not supported!");  return nullptr;
		case RendererAPI::API::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices);

		}

		SP_CORE_ASSERT(false, "No such RendererAPI supported.");
		return nullptr;
	}
}