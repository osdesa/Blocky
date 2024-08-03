#include "graphics/SpriteSheet.h"

namespace Blocky {
	SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, Vec2 min, Vec2 max)
	{
		//Sets the texture
		texture = std::move(texture);
		// Sets the texture coordinates
		TexCoords[0] = min.x;
		TexCoords[1] = min.y;

		TexCoords[2] = max.x;
		TexCoords[3] = min.y;

		TexCoords[4] = max.x;
		TexCoords[5] = max.y;

		TexCoords[6] = min.x;
		TexCoords[7] = max.y;
	}

	SpriteSheet SpriteSheet::CreateFromCoords(std::shared_ptr<Texture> texture, Vec2 Coords, Vec2 spriteSize)
	{
		// Calulates the texture coordinates from the texture size and its posistion in the space
		float textureCoords[] = {
			{(Coords.x * spriteSize.x) / texture->GetWidth()},
			{ (Coords.y * spriteSize.y) / texture->GetHeight() },

			{ ((Coords.x + 1) * spriteSize.x) / texture->GetWidth() },
			{ ((Coords.y + 1) * spriteSize.y) / texture->GetHeight() }
		};
		// Creates a spritesheet with the texture coordinates and the given texture
		return SpriteSheet(texture, Vec2(textureCoords[0], textureCoords[1]), Vec2(textureCoords[2], textureCoords[3]));
	}
}