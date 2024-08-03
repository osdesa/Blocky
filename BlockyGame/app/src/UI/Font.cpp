#include "UI/Font.h"
#include "logger.h"
#include "glad/glad.h"
#include <string>  
#include "core/GameState.h"

namespace Blocky {
	Font::~Font()
	{
		Logger::output(INFO, "destroying font handler");
	}

	void Font::Create(std::string dir, std::string name)
	{
		// inits variables
		directory = dir; fontName = name;
		// inits the freetype handle
		if (FT_Init_FreeType(&ft))
			Logger::output(FATAL, "Could not init FreeType Library");
		// loads the font
		if (FT_New_Face(ft, (dir + fontName).c_str(), 0, &face))
			Logger::output(FATAL, "Failed to load font");
		// tests if loading glyphs works
		FT_Set_Pixel_Sizes(face, 0, 48);
		if (FT_Load_Char(face, 'Y', FT_LOAD_RENDER))
			Logger::output(FATAL, "Failed to load Glyph");

		Logger::output(INFO, "Font handler init");
		// Sets glyph size
		FT_Set_Pixel_Sizes(face, 0, 48);
		// loads all the characters
		InitCharacters();
		// creates the vertex array
		va.Create();
		va.Bind();
		// Creates an empty vertex buffer which will be populated once the characters have been created
		vb.CreateEmpty(sizeof(float) * 6 * 4, GL_DYNAMIC_DRAW);

		// states that the glyphs will provied with 4 floats
		VBLayout layout{};
		layout.Push(GL_FLOAT, 4, GL_FALSE);
		va.AddBuffer(vb, layout);

		// Creates the shader for the font handler
		shader.Create("app/res/shaders/fontVert.glsl", "app/res/shaders/fontFragment.glsl");
	}

	void Font::InitCharacters()
	{
		// states how the textures will loaded into gpu memory
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//  loops through all standard ascii characters
		for (unsigned char c = 0; c < 255; c++)
		{
			// trys to load the characters
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				Logger::output(FATAL, "Failed to load Glyph %c", c);
				continue;
			}

			// creates a texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			// sets up a texture which is only 8 bytes and values are given by the glyph
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
				face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

			// creates a character struct with the given parameters
			Character character = {
				texture,
				Vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				Vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			// states how openGL should handle the texture when sampling and what to do if the texture is to small
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// adds the character to the character dictionary
			Characters.insert(std::pair<char, Character>(c, character));
		}
		// unbinds the texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// Frees up the font and font handle
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

	}

	void Font::SetProjection(Camera camera)
	{
		shader.Bind();
		shader.SetMatrix4("projection", camera.GetTextProjection());
	}

	void Font::AddText(std::string text, float x, float y, float scale, Vec3 color, bool clear, uint32_t id)
	{
		// adds text to the text vector
		queuedText.push_back({ text, x, y, scale, color, clear, id });
	}

	void Font::RenderText()
	{
		int index = 0;
		// loops through every bit of text in the vector
		for (auto text : queuedText) {
			// binds the texture and sends colour
			shader.Bind();
			shader.SetUniform3f("textColor", text.Colour.x, text.Colour.y, text.Colour.z);
			glActiveTexture(GL_TEXTURE0);
			va.Bind();

			// The character which needs to be written
			std::string::const_iterator c;
			for (c = text.text.begin(); c != text.text.end(); c++)
			{
				// Gets the data about the character from the dictionary
				Character ch = Characters[*c];

				// gets the x posistion of the font based on where it is in the font and the scale
				float xpos = text.x + ch.Bearing.x * text.scale;
				// same as xpos but uses - as reads from bottom to top
				float ypos = text.y - (ch.Size.y - ch.Bearing.y) * text.scale;

				// gets the width of the character
				float w = ch.Size.x * text.scale;
				// Gets the height of the character
				float h = ch.Size.y * text.scale;

				// Sets the vertices of where the posistions are and where the textures are
				float vertices[6][4] = {
					{ xpos,     ypos + h,   0.0f, 0.0f },
					{ xpos,     ypos,       0.0f, 1.0f },
					{ xpos + w, ypos,       1.0f, 1.0f },

					{ xpos,     ypos + h,   0.0f, 0.0f },
					{ xpos + w, ypos,       1.0f, 1.0f },
					{ xpos + w, ypos + h,   1.0f, 0.0f }
				};
				// binds the texture
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);

				// Binds the vertex buffer
				vb.Bind();
				// Adds data to the vertex buffer
				vb.AddedData(vertices, sizeof(vertices));
				vb.UnBind();

				// Draws the character
				DrawArray(va, shader, 6);
				// moves along the character by the size of character / 6 and then scaled
				text.x += (ch.Advance >> 6) * text.scale;
			}
		}
		// loops through all the text
		for (int i = 0; i < queuedText.size(); i++) {
			// if the text should be cleard 
			if (queuedText[i].toClear) {
				queuedText.erase(queuedText.begin() + i);
			}
		}
		// make the queue the smallest size possible
		queuedText.shrink_to_fit();
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	float Font::GetTextSize(std::string text, float scale)
	{
		float size = 0;
		// loops through every character in text
		for (char c : text) {
			Character ch = Characters[c];
			// attempt at guess how big the text will be but does not account for characters going together
			// eg qu may have less spacing in some fonts
			size += ch.Size.x * scale;
		}
		size += text.size() * 2;
		return size;
	}

	void Font::Clear()
	{
		queuedText.clear();
	}

	void Font::Update(uint32_t id, char c, bool reset)
	{
		// loops through all the text
		for (int i = 0; i < queuedText.size(); i++) {
			if (queuedText[i].id == id)
			{
				// if the character is the delete key
				if ((int)c == 3) {
					// create temp of message
					std::string temp = queuedText[i].text;
					// if the string has text
					if (temp.size() > 1) {
						// remove one character
						temp.resize(temp.size() - 1);
						queuedText[i].text = temp;
					}
					else {
						// otherwise set as empty
						queuedText[i].text = "";
					}
				}
				// if character which should be writable
				if ((c > 32) && (c < 128))
				{
					// if the input box has not been writen into
					if (reset)
						queuedText[i].text = c;
					else
						queuedText[i].text += c;
				}
				// set the current text
				GameState::currentText = queuedText[i].text;
			}
		}
	}
}