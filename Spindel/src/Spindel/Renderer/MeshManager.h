#pragma once

#include <vector>

#include "Spindel/Core/Core.h"
#include "Spindel/Renderer/Mesh.h"
#include "Spindel/Renderer/Model.h"

namespace Spindel
{

	class MeshManager
	{
	public:
		static void Init();
		static Ref<Mesh> CreateMesh(const std::string& name);
		static Ref<Mesh> CreateMesh(const std::string& name, Ref<VertexArray>& vao, Ref<VertexBuffer>& vbo, Ref<IndexBuffer>& ibo, std::vector<Ref<Texture2D>>& textures);
		static Ref<Model> CreateModel(const std::string& path);

		static Ref<Mesh> CreateCube(const std::string& name);
		static Ref<Mesh> CreatePlane(const std::string& name);

		static Ref<Mesh> GetMesh(const std::string& name);
		static Ref<Model> GetModel(const std::string& name);
		static std::vector<Ref<Mesh>> GetAllMeshes();
		static std::vector<Ref<Model>> GetAllModels();
	private:
	};

}