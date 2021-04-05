#include "sppch.h"
#include "Renderer.h"
#include "Spindel/Renderer/Resources/Texture.h"

#include "Spindel/Assets/AssetManager.h"



namespace Spindel {

	RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPIType::OpenGL;

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
		//Ref<RenderPass> m_ActiveRenderPass;
		RenderCommandQueue m_CommandQueue;

		Ref<VertexBuffer> m_FullscreenQuadVertexBuffer;
		Ref<IndexBuffer> m_FullscreenQuadIndexBuffer;
		//Ref<Pipeline> m_FullscreenQuadPipeline;
	};

	static RendererData s_Data;


	struct RendererDataOld
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

	static RendererDataOld s_DataOld;

	void Renderer::Init()
	{
		Renderer::Submit([]() { RendererAPI::Init(); });
		AssetManager::loadAsset(Loader::Type::shader, "grid", "assets/shaders/Grid.glsl");
		AssetManager::loadAsset(Loader::Type::shader, "texture", "assets/shaders/Texture.glsl");
		s_DataOld.TextureShader = AssetManager::getShader("texture");
		s_DataOld.TextureShader->Bind();
		s_DataOld.TextureShader->SetInt("u_Texture", 0);

		float vertices[6 * 3] =
		{
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f,
		0.f, 0.f, 0.f
		};


		s_DataOld.QuadVertexArray = VertexArray::Create();

		s_DataOld.QuadVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		s_DataOld.QuadVertexBuffer->SetLayout(layout);
		s_DataOld.QuadVertexArray->AddVertexBuffers(s_DataOld.QuadVertexBuffer);
	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		s_DataOld.TextureShader->Bind();
		s_DataOld.TextureShader->SetMat4("u_ViewProjection", camera.GetProjection() * glm::inverse(transform));
		s_DataOld.ViewProjectionMatrix = camera.GetProjection();
	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_DataOld.TextureShader->Bind();
		s_DataOld.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
		s_DataOld.ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}
	void Renderer::Clear()
	{
		Renderer::Submit([]() {
			RendererAPI::Clear(0.0f, 0.0f, 0.0f, 1.0f);
			});
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		Renderer::Submit([=]() {
			RendererAPI::Clear(r, g, b, a);
			});
	}

	void Renderer::ClearMagenta()
	{
		Clear(1, 0, 1);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
	}

	void Renderer::DrawIndexed(uint32_t count, PrimitiveType type, bool depthTest)
	{
		Renderer::Submit([=]() {
			RendererAPI::DrawIndexed(count, type, depthTest);
			});
	}

	void Renderer::SetLineThickness(float thickness)
	{
		Renderer::Submit([=]() {
			RendererAPI::SetLineThickness(thickness);
			});
	}


	void Renderer::WaitAndRender()
	{
		s_Data.m_CommandQueue.Execute();
	}


	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const glm::mat4& transform, const std::vector<Ref<Texture2D>>& texs)
	{
		s_DataOld.TextureShader->Bind();
		s_DataOld.TextureShader->SetMat4("u_Transform", transform);
		for (unsigned int i = 0; i < texs.size(); i++)
		{
			texs[i]->Bind(i);
		}
		vertexArray->Bind();
		Renderer::DrawIndexed(vertexArray->GetIndexBuffer()->GetCount(), PrimitiveType::Triangles);
	}

	void Renderer::SubmitMesh(Ref<Mesh> mesh, const glm::mat4& transform)
	{
		mesh->Draw(transform);
	}

	RenderCommandQueue& Renderer::GetRenderCommandQueue()
	{
		return s_Data.m_CommandQueue;
	}


}