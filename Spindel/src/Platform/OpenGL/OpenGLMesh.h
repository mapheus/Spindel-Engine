#pragma once
#include "Spindel/Core/Core.h"

#include "Spindel/Renderer/Mesh.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Buffer.h"

#include <string>
#include <vector>

#include "glm/glm.hpp"

namespace Spindel {
	class OpenGLMesh : Mesh
	{
	public:
		OpenGLMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<class Texture*>& textures);
		virtual ~OpenGLMesh();

	private:
		virtual void SetupMesh() override;
	private:
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<IndexBuffer> m_Ibo;
		std::vector<Texture> m_Tex;

		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;

	};

}
