#pragma once

#include <string>

#include "Spindel/Core/Core.h"
#include "Spindel/Core/IO/Resource.h"


#include <stb_image.h>

namespace Spindel {

	class Texture : public Resource
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;
		virtual std::string GetName() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path, const std::string& name = "Default");
		static Ref<Texture2D> Create(stbi_uc* data, uint32_t width, uint32_t height, uint32_t channels);
	};

}