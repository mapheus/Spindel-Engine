#pragma once

#include "Loader.h"

namespace Spindel
{

	class ImageLoader : public Loader
	{
	public:
		explicit ImageLoader(Cache& initCache);
		bool loadAsset(Bundle& bundle, const std::string& name, const std::string& filename, bool mipmaps = true);


	};
}