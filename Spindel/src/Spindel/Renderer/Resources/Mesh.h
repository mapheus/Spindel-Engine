#pragma once

#include "glm/glm.hpp"
#include "Spindel/Renderer/Buffer.h"
#include "Spindel/Renderer/VertexArray.h"
#include "Spindel/Renderer/Resources/Texture.h"

#include "Spindel/Core/IO/Resource.h"

#include <vector>

namespace Spindel {

	class Material;

	class Mesh : public Resource
	{
	public:
		virtual ~Mesh() = default;

		virtual void Draw(Ref<Material>& material, const glm::mat4& transform) = 0;

		//virtual std::vector<Ref<Mesh>> GetChildren() = 0;


		static Ref<Mesh> Create(const std::string& name);
		static Ref<Mesh> Create(Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
	private:
	};
}