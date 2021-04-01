#pragma once

#include "RenderCommand.h"
#include "Spindel/Renderer/Camera.h"
#include "Spindel/Renderer/EditorCamera.h"
#include "Spindel/Renderer/Resources/Shader.h"
#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Mesh.h"

namespace Spindel {

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static void Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f), const std::vector<Ref<Texture2D>>& texs = std::vector<Ref<Texture2D>>());
		static void DrawMesh(Ref<Mesh> mesh, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};
}