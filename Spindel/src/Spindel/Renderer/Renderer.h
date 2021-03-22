#pragma once

#include "RenderCommand.h"
#include "Spindel/Renderer/PerspectiveCamera.h"
#include "Spindel/Renderer/EditorCamera.h"
#include "Spindel/Renderer/Shader.h"

#include "Spindel/Renderer/Model.h"

namespace Spindel {

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(PerspectiveCamera& camera);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const std::vector<Ref<Texture2D>>& texs = std::vector<Ref<Texture2D>>());
		static void DrawMesh(const Ref<Model>& model, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};
}