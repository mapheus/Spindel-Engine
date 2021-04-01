#pragma once

#include "Cache.h"

namespace Spindel
{

	class AssetManager
	{
	public:
		static void Init(Ref<Cache> cache, Ref<Bundle> bundle);
		static void loadAsset(Loader::Type loaderType, const std::string& name, const std::string& filename, bool mipmaps = true);

		static Ref<Texture2D> getTexture(const std::string& name);
		static const Ref<Shader> getShader(const std::string& name);
		static const Ref<Mesh> getMesh(const std::string& name);
	private:

	};
}