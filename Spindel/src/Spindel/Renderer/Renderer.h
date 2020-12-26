#pragma once

#include "RenderCommand.h"
#include "Spindel/Renderer/PerspectiveCamera.h"
#include "Spindel/Renderer/Shader.h"

namespace Spindel {

	class Renderer
	{
	public:
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}