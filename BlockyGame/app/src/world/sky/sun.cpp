#include "world/sky/sun.h"

namespace Blocky {
	void Sun::Create(Camera& camera)
	{
		// Creates the vertex array
		va.Create();
		va.Bind();

		// Creates the vertex buffer with the sun data
		vb.Create(&rect, 40 * sizeof(float));
		vb.Bind();
		// Creates the indices buffer with the need instructions to draw the sun
		ib.Create(indices, 12);
		ib.Bind();
		// Creates the sun texture
		texture.Create("app/res/textures/sun.png", GL_NEAREST);
		texture.Bind();
		// Creates the sun shader
		shader.Create("app/res/shaders/skyVert.glsl", "app/res/shaders/skyFrag.glsl");
		shader.Bind();
		// Tells the GPU the data will be sent as a vec3 and vec2
		VBLayout layout{};
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		va.AddBuffer(vb, layout);
	}
}
