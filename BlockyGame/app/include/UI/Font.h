#pragma once

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "math/BMath.h"
#include <map>
#include "graphics/Texture.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/renderer.h"
#include <camera.h>

namespace Blocky {
	class Font : Renderer
	{
	public:
		Font() {};
		~Font();
		void Create(std::string dir, std::string name);
		void InitCharacters();
		void SetProjection(Camera camera);
		void AddText(std::string text, float x, float y, float scale, Vec3 color, bool clear, uint32_t id);
		void RenderText();
		float GetTextSize(std::string text, float scale);
		void Clear();
		void Update(uint32_t id, char c, bool reset);
	private:
		struct Character {
			unsigned int TextureID;
			Vec2   Size;
			Vec2   Bearing;
			unsigned int Advance;
		};
		struct Text {
			std::string text;
			float   x;
			float   y;
			float   scale;
			Vec3	Colour;
			bool	toClear;
			uint32_t id;
		};
		Shader shader;
		VertexArray va;
		VertexBuffer vb;
		VBLayout layout{};

		std::vector<Text> queuedText;
		std::map<char, Character> Characters;

		FT_Library ft;
		FT_Face face;

		std::string fontName;
		std::string directory;
	};
};