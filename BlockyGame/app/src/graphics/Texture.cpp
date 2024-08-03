#include "graphics/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Image/stb_image.h"
#include <logger.h>
#include <UI/Font.h>

namespace Blocky {
    void Texture::Create(const char* filePath, GLenum type)
    {
        // Sets the texture type
        textureType = GL_TEXTURE_2D;
        // inits the variables
        id = 0; path = filePath; width = 0; height = 0; imageData = 0; PixelDataSize = 0;
        // flips the image to make sure it is how it was draw
        stbi_set_flip_vertically_on_load(1);
        // loads the image file in
        imageData = stbi_load(path, &width, &height, &PixelDataSize, 4);
        // creates a texture handle
        glGenTextures(1, &id);
        // binds the texture id making this texture active
        glBindTexture(GL_TEXTURE_2D, id);

        // Sets up parameters for the texture
        // Tells the gpu how to handle picking the pixel from the image in low def
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
        // Tells the gpu how to handle picking the pixel from the image in high def
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
        // Tells the gpu how to handle the image how to strech the image in the x axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // Tells the gpu how to handle the image how to strech the image in the y axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Creates the texture on teh gpu with all the needed data telling the GPU
        // it ill have red,green,blue and alpha each using 8 bytes
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glBindTexture(GL_TEXTURE_2D, 0);
        // if successful clear free the image
        if (imageData) {
            stbi_image_free(imageData);
        }
    }

    void Texture::GlyphCreation(FT_Face face)
    {
        // sets the texture type
        textureType = GL_TEXTURE_2D;
        // creates a texture handle
        glGenTextures(1, &id);
        // binds the texture
        glBindTexture(GL_TEXTURE_2D, id);

        // Creates the texture on teh gpu with all the needed data telling the GPU
        // it ill have only red meaning only 8 bytes
        // sets the size to be the glyph size

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer
        );

        // Tells the gpu how to handle the image how to strech the image in the x axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // Tells the gpu how to handle the image how to strech the image in the y axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Tells the gpu how to handle picking the pixel from the image in low def
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // Tells the gpu how to handle picking the pixel from the image in high def
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    void Texture::Bind(uint32_t textureSlot)
    {
        // binds the texture at the given slot
        glActiveTexture(GL_TEXTURE0 + textureSlot);
        glBindTexture(textureType, id);
    }

    void Texture::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}