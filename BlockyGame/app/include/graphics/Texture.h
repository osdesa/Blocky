#pragma once

#include "renderer.h"
#include "glad/glad.h"
#include "UI/Font.h"

namespace Blocky {
	class Texture
	{
	private:
		uint32_t id;
		const char* path;

		unsigned char* imageData;
		int width;
		int height;
		int PixelDataSize;
		GLenum textureType;

	public:
		Texture() = default;
		~Texture();

		Texture& operator=(Texture&& rhs) noexcept {
			std::swap(id, rhs.id);
			std::swap(textureType, rhs.textureType);
			return *this;
		}
		Texture(Texture&& rhs) noexcept
		{
			std::swap(id, rhs.id);
			std::swap(textureType, rhs.textureType);
		}

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Create(const char* filepath, GLenum type);
		void GlyphCreation(FT_Face face);

		void Bind(uint32_t textureSlot = 0);
		void UnBind();


		inline uint32_t GetId() { return  id; }
		inline int GetWidth() { return  width; }
		inline int GetHeight() { return  height; }
		inline int GetPDS() { return  PixelDataSize; }
	};
}