#pragma once

#include "Spindel/Core/Core.h"

#include "glm/glm.hpp"

namespace Spindel {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};


	class Mesh
	{
	public:
		virtual ~Mesh() = default;

		static Ref<Mesh> Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<class Texture*>& textures);
	private:
		virtual void SetupMesh() = 0;

	};
}