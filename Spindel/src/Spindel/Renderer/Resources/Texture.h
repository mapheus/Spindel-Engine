#pragma once

#include <string>

#include "Spindel/Core/Core.h"
#include "Spindel/Core/IO/Resource.h"


#include <stb_image.h>

namespace Spindel {

	enum class TextureFormat
	{
		None = 0,
		RGB = 1,
		RGBA = 2,
		Float16 = 3
	};

	enum class TextureWrap
	{
		None = 0,
		Clamp = 1,
		Repeat = 2
	};



	class Texture : public RefCounted
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

	class TextureCube : public Texture
	{
	public:
		static Ref<TextureCube> Create(TextureFormat format, uint32_t width, uint32_t height);
		static Ref<TextureCube> Create(const std::string& path);

		virtual const std::string& GetPath() const = 0;
	};

}