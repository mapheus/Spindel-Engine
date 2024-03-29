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
		virtual std::string& GetName() = 0;

		static Ref<Mesh> Create(const std::string& name);
		static Ref<Mesh> Create(const std::string& name, Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
	private:
	};
}