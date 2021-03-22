#pragma once
#include "Spindel/Assets/Asset.h"
#include "Spindel/Core/Core.h"

#include <vector>

namespace Spindel
{
	class AssetManager
	{
	public:
		AssetManager();
		std::vector<Ref<Asset>>& GetAssets() { return m_Assets; }
	private:
		std::vector<Ref<Asset>> m_Assets;

	};
}