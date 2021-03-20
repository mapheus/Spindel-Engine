#pragma once

#include "glm/glm.hpp"
#include "Spindel/Renderer/Buffer.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Texture.h"

namespace Spindel {

	class Mesh
	{
	public:
		virtual ~Mesh() = default;

		virtual void Draw(const glm::mat4& transform) = 0;

		static Ref<Mesh> Create();
		static Ref<Mesh> Create(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
	private:
	};
}