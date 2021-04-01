#pragma once

#include "Cache.h"

namespace Spindel
{

	class AssetManager
	{
	public:
		static void Init(Ref<Cache> cache, Ref<Bundle> bundle);
		static void loadAsset(Loader::Type loaderType, const std::string& name, const std::string& filename, bool mipmaps = true);
	private:

	};
}