#include "sppch.h"
#include "AssetManager.h"

namespace Spindel
{
	struct AssetsData
	{
		Ref<Cache> cache;
		Ref<Bundle> bundle;
	};
	static AssetsData s_AssetsData;
	void AssetManager::Init(Ref<Cache> cache, Ref<Bundle> bundle)
	{
		s_AssetsData.cache = Ref<Cache>::Create();
		s_AssetsData.bundle = Ref<Bundle>::Create(s_AssetsData.cache);
		s_AssetsData.bundle->loadAsset(Loader::Type::image, "bomb", "assets/textures/bomb.png");
		s_AssetsData.bundle->loadAsset(Loader::Type::staticMesh, "asd", "assets/models/test/test.fbx");
	}
	void AssetManager::loadAsset(Loader::Type loaderType, const std::string& name, const std::string& filename, bool mipmaps)
	{
		s_AssetsData.bundle->loadAsset(loaderType, name, filename, mipmaps);
	}
}