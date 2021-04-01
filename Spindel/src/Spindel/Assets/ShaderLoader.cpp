#include "sppch.h"
#include "ShaderLoader.h"

#include <fstream>


namespace Spindel
{
	ShaderLoader::ShaderLoader(Cache& cache)
		: Loader{cache, Loader::Type::shader}
	{
	}
	bool ShaderLoader::loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps)
	{
		std::string result;
		std::ifstream in(filename, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
		}
		else
		{
			SP_CORE_ASSERT(false, "Could not load shader!");
		}
		in.close();
		bundle.setShader(name, Shader::Create(result));
		return true;
	}
}