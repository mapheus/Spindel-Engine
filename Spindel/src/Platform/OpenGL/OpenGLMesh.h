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

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh();
		OpenGLMesh(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
		virtual ~OpenGLMesh();

		void Draw(const glm::mat4& transform) override;
	private:
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<IndexBuffer> m_Ibo;
		Ref<BufferLayout> m_Layout;

		std::vector<Ref<Texture2D>> m_Textures;

		std::string m_Name;
	};
}