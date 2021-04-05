#pragma once

#include "Spindel/Renderer/Camera.h"
#include "Spindel/Renderer/EditorCamera.h"
#include "Spindel/Renderer/Resources/Shader.h"
#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Mesh.h"

#include "Spindel/Renderer/RenderCommandQueue.h"

#include "Spindel/Renderer/RendererAPI.h"

namespace Spindel {

	class Renderer
	{
	public:
		// Commands
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void DrawIndexed(uint32_t count, PrimitiveType type, bool depthTest = true);

		// For OpenGL
		static void SetLineThickness(float thickness);

		static void ClearMagenta();

		static void Init();
		static void WaitAndRender();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const std::vector<Ref<Texture2D>>& texs = std::vector<Ref<Texture2D>>());
		static void SubmitMesh(Ref<Mesh> mesh, const glm::mat4& transform = glm::mat4(1.0f));

		template<typename FuncT>
		static void Submit(FuncT&& func)
		{
			auto renderCmd = [](void* ptr) {
				auto pFunc = (FuncT*)ptr;
				(*pFunc)();

				// NOTE: Instead of destroying we could try and enforce all items to be trivally destructible
				// however some items like uniforms which contain std::strings still exist for now
				// static_assert(std::is_trivially_destructible_v<FuncT>, "FuncT must be trivially destructible");
				pFunc->~FuncT();
			};
			auto storageBuffer = GetRenderCommandQueue().Allocate(renderCmd, sizeof(func));
			new (storageBuffer) FuncT(std::forward<FuncT>(func));
		}

	private:
		static RenderCommandQueue& GetRenderCommandQueue();
	};
}