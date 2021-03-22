#pragma once
#include "Spindel/Renderer/Mesh.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Buffer.h"

#include "glm/glm.hpp"

#include "Spindel/Renderer/Texture.h"
#include "Spindel/Renderer/Shader.h"

#include "Spindel/Core/Core.h"

namespace Spindel
{


	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(const std::string& name);
		OpenGLMesh(const std::string& name, Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
		virtual ~OpenGLMesh();

		void Draw(const glm::mat4& transform) override;
		std::string& GetName() override { return m_Name; }
	private:
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<IndexBuffer> m_Ibo;
		Ref<BufferLayout> m_Layout;

		std::vector<Ref<Texture2D>> m_Textures;

		std::string m_Name;

		int m_Index;
	};
}