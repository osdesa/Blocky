#include "world/sky/moon.h"

namespace Blocky{
	void Moon::Create(Camera& camera)
	{
		// Creates the vertex array
		va.Create();
		va.Bind();
		// Creates the vertex buffer with the vertices and the size
		vb.Create(&rect, 40 * sizeof(float));
		vb.Bind();
		// Sets the indices buffer to have the instructions to draw the square
		ib.Create(indices, 12);
		ib.Bind();
		// sets the texture of the moon
		texture.Create("app/res/textures/moon.png", GL_NEAREST);
		texture.Bind();
		// Creates the shader for the moon
		shader.Create("app/res/shaders/skyVert.glsl", "app/res/shaders/skyFrag.glsl");
		shader.Bind();
		// Sets the moon to be setting
		angle = PI;
		// States to the GPU that the data will be sent as a vec3 and a vec2
		VBLayout layout{};
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		va.AddBuffer(vb, layout);
	}
}