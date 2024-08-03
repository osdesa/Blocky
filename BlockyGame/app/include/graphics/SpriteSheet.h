#pragma once
#include "renderer.h"
#include "Texture.h"
#include <memory>
#include "math/BMath.h"

namespace Blocky {
	class SpriteSheet

	{
	public:
		SpriteSheet(std::shared_ptr<Texture> texture, Vec2 min, Vec2 max);

		std::shared_ptr<Texture> GetTexture() { return texture; }
		float* GetTextureCoords() { return TexCoords; }


		static SpriteSheet CreateFromCoords(std::shared_ptr<Texture> texture, Vec2 Coords, Vec2 spriteSize);
	private:
		std::shared_ptr<Texture> texture;

		float TexCoords[8];
	};
}