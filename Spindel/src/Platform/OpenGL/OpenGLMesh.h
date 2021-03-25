#pragma once

#include "Spindel/Renderer/Resources/Mesh.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Buffer.h"

#include "glm/glm.hpp"

#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Shader.h"

#include "Spindel/Core/Core.h"

namespace Spindel
{
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(const std::string& name);
		OpenGLMesh(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
		virtual ~OpenGLMesh();

		void Draw(const glm::mat4& transform) override;

	private:
		bool m_Root = false;

		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<IndexBuffer> m_Ibo;
		Ref<BufferLayout> m_Layout;

		std::vector<Ref<Texture2D>> m_Textures;
	};
}