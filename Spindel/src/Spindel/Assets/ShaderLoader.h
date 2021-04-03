#pragma once
#include "Spindel/Renderer/Resources/Shader.h"

#include "Loader.h"

#include "Bundle.h"

namespace Spindel
{

	class ShaderLoader : public Loader
	{
	public:
		ShaderLoader(Cache& cache);
		bool loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps = true);
	private:

	};
}