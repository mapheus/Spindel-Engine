#pragma once

#include "RenderCommand.h"
#include "Spindel/Renderer/PerspectiveCamera.h"
#include "Spindel/Renderer/Shader.h"

namespace Spindel {

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}