#include "sppch.h"
#include "MeshManager.h"

namespace Spindel
{
	Ref<Mesh> MeshManager::CreateMesh()
	{
		Ref<Mesh> m = Mesh::Create();
		m_Meshes.push_back(m);
		return m;
	}
	std::vector<Ref<Mesh>> MeshManager::GetAllMeshes()
	{
		return m_Meshes;
	}
}