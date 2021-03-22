#include "sppch.h"
#include "Spindel/Assets/AssetManager.h"

#include <filesystem>
#include <string>

namespace Spindel
{
	AssetManager::AssetManager()
	{

		int depth = 0;
		static std::filesystem::path currentfolder;
		std::function<void(const std::filesystem::path&, unsigned int, unsigned int&)> functor = [&](
			const std::filesystem::path& path,
			unsigned int depth, unsigned int& idx) {
				for (auto&& p : std::filesystem::directory_iterator(path)) {
					if (std::filesystem::is_directory(p.path())) {
						functor(p, depth + 1, ++idx);
					}
					else {
						Ref<Asset> m = CreateRef<Asset>(p.path().filename().string(), p.path().relative_path().string());
						m_Assets.push_back(m);
					}
					++idx;
				}
				depth -= 1;
		};
		unsigned int dir_idx = 0u;
		functor(std::filesystem::current_path(), 0u, dir_idx);
	}

}