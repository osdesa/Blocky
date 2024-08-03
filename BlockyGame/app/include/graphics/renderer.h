#pragma once

#include "glad/glad.h"
#include "VertexArray.h"
#include "shader.h"
#include "IndexBuffer.h"
#include <core/window.h>

namespace Blocky {
	class Renderer
	{
	private:

	public:
		Renderer() {};
		void Clear(Vec3& skyColour);
		void DrawElements(VertexArray& vertex, IndexBuffer& index, Shader& shader);
		void DrawArray(VertexArray& vertex, Shader& shader, uint32_t count);
		void NewFrame(Window* win);
	};
}