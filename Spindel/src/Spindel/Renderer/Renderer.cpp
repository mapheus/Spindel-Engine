#include "sppch.h"
#include "Renderer.h"
#include "Spindel/Renderer/Resources/Texture.h"

namespace Spindel {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct RendererData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		
		glm::mat4 ViewProjectionMatrix = glm::mat4(1);

		glm::vec4 QuadVertexPositions[4];
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		RenderCommand::Init();

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetProjection() * glm::inverse(transform));
		s_Data.ViewProjectionMatrix = camera.GetProjection();
	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
		s_Data.ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}
	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform, const std::vector<Ref<Texture2D>>& texs)
	{
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		for (unsigned int i = 0; i < texs.size(); i++)
		{
			texs[i]->Bind(i);
		}
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::DrawMesh(Ref<Mesh> mesh, const glm::mat4& transform)
	{
		mesh->Draw(transform);
	}

}