#include "sppch.h"
#include "ImageLoader.h"
#include "Spindel/Assets/Bundle.h"
#include "Spindel/Renderer/Resources/Texture.h"

#include <stb_image.h>

namespace Spindel
{
	ImageLoader::ImageLoader(Cache& initCache)
		: Loader{initCache, Type::image}
	{

	}
	bool ImageLoader::loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		//Resource::SetPath(path.c_str());

		data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
		SP_CORE_ASSERT(data, "Failed to load image! Path: {0}", filename.c_str());

		Ref<Texture2D> t = Texture2D::Create(data, width, height, channels);
		bundle.setTexture(name, t);
		stbi_image_free(data);
		return true;
	}
}