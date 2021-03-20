#pragma once

#include <vector>

#include "Spindel/Renderer/Mesh.h"

namespace Spindel
{

	class MeshManager
	{
	public:
		static Ref<Mesh> CreateMesh();
		static Ref<Mesh> CreateMesh(std::string& path);

		static Ref<Mesh> GetMesh(const std::string& name);
		static std::vector<Ref<Mesh>> GetAllMeshes();
	private:
		static std::vector<Ref<Mesh>> m_Meshes;
	};

}