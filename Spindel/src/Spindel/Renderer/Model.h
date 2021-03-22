#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include "Spindel/Core/Core.h"
#include "Spindel/Renderer/Texture.h"
#include "Spindel/Renderer/Mesh.h"
#include "Spindel/Renderer/Buffer.h"

namespace Spindel {


	class Model
	{
	public:
		Model(const std::string& path);

		void Draw(const glm::mat4& transform);

		const std::string& GetName() const { return m_Name; }
	private:
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);


	private:
		std::vector<Ref<Texture2D>> m_TexturesLoaded;
		std::vector<Ref<Mesh>> m_Meshes;
		std::string m_Directory;
		std::string m_Name = "M";
	};

}