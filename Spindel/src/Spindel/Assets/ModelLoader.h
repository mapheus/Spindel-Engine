#pragma once
#include "Loader.h"

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Spindel/Renderer/Resources/Texture.h"
#include "Spindel/Renderer/Resources/Mesh.h"


#include "Spindel/Assets/Cache.h"

namespace Spindel
{

	class ModelLoader : public Loader
	{
	public:
		ModelLoader(Cache& cache);
		bool loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps = true);

		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

	private:
		Bundle* m_Bundle = nullptr;
		std::string m_Directory;
	};
}