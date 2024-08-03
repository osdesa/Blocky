#include "graphics/primitives/rect.h"

namespace Blocky {
	void Rect::RCreate(Camera& camera, Vec2 left, Vec2 right, Vec3 color)
	{
		// Sets the varibles
		leftBottom = left;
		rightTop = right;
		// Creates the vertex array
		va.Create();
		va.Bind();

		// The posistion of the corners of the rectangle
		float verts[8] = {
			right.x,    right.y,
			left.x,     right.y,
			left.x,	    left.y,
			right.x,	left.y
		};

		// Creates the vertex buffer which holds the vertex postitions
		vb.Create(&verts, sizeof(float) * 8);

		// Creates the layout struct which tells the GPU
		// States the data should be read as two normilsed floats
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		// Adds the vertex buffer and its layout to the vertex array
		va.AddBuffer(vb, layout);
		vb.UnBind();
		// Creates the index buffer
		ib.Create(indices, 6);
		ib.Bind();
		// Creates the shaders by reading the data from the given files
		shader.Create("app/res/shaders/buttonVert.glsl", "app/res/shaders/buttonFrag.glsl");
		shader.Bind();
		// Sends data to the gpu about projection matrix
		shader.SetMatrix4("projection", camera.GetTextProjection());
		// Sends data to the gpu about colour of text
		shader.SetUniform3f("backColour", color.x, color.y, color.z);

	}

	void Rect::RCreateTextured(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, std::string fileName)
	{
		// Sets the variables
		leftBottom = left;
		rightTop = right;
		// Creates the vao
		va.Create();
		va.Bind();

		// Sets the posisitions of the corners and there texture coordinates
		float verts[16] = {
			right.x,    right.y, 1.0f, 1.0f,
			left.x,     right.y, 0.0f, 1.0f,
			left.x,	    left.y,  0.0f, 0.0f,
			right.x,	left.y,  1.0f, 0.0f
		};

		// Creates the vertex buffer with the data
		vb.Create(&verts, sizeof(float) * 16);

		// Creates layout and states it should be read as a vec2 and vec2
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		// Adds buffer to vao
		va.AddBuffer(vb, layout);
		vb.UnBind();

		// Creates index buffer from the indices
		ib.Create(indices, 6);
		ib.Bind();

		// Gets the filepath
		std::string FilePath = "app/res/textures/" + fileName;
		// Creates the texture from the file path with the nearest setting as it looks best for rects
		texture.Create(FilePath.c_str(), GL_NEAREST);
		texture.Bind();

		// Creates the shader
		shader.Create("app/res/shaders/btnTexturedVert.glsl", "app/res/shaders/btnTextureFrag.glsl");
		shader.Bind();
		// Sends matrix to the gpu
		shader.SetMatrix4("projection", camera.GetTextProjection());
	}

	void Rect::RDraw()
	{
		// If the rect has a texture bind it
		if (texture.GetId() != 0) {
			texture.Bind();
		}
		// Draw the rectangle
		DrawElements(va, ib, shader);
	}

	void Rect::RChangeColour(Vec3 colour)
	{
		// Bind the shader
		shader.Bind();
		// Send the new colour as 3 seperate floats
		shader.SetUniform3f("backColour", colour.x, colour.y, colour.z);
	}

	bool Rect::RIntersect(Vec2 pos)
	{
		// if the posistion is within the x bounds of the rect
		if ((leftBottom.x < pos.x) && (rightTop.x > pos.x)) {
			// if the posistion is within the y bounds of the rect
			if ((leftBottom.y < pos.y) && (rightTop.y > pos.y)) {
				return true;
			}
		}
		return false;
	}
}