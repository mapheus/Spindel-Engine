#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "VertexArray.h"

namespace Spindel {

	using RendererID = uint32_t;

	enum class RendererAPIType
	{
		None,
		OpenGL
	};

	// TODO: move into separate header
	enum class PrimitiveType
	{
		None = 0, Triangles, Lines
	};

	struct RenderAPICapabilities
	{
		std::string Vendor;
		std::string Renderer;
		std::string Version;

		int MaxSamples = 0;
		float MaxAnisotropy = 0.0f;
		int MaxTextureUnits = 0;
	};


	class RendererAPI
	{
	public:
		static void Init();
		static void Shutdown();

		static void Clear(float r, float g, float b, float a);
		static void SetClearColor(float r, float g, float b, float a);


		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void DrawIndexed(uint32_t count, PrimitiveType type, bool depthTest = true, bool faceCulling = true);
		static void SetLineThickness(float thickness);

		static RenderAPICapabilities& GetCapabilities()
		{
			static RenderAPICapabilities capabilities;
			return capabilities;
		}

		static RendererAPIType Current() { return s_CurrentRendererAPI; }
	private:
		static RendererAPIType s_CurrentRendererAPI;
	};
}