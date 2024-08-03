#include "graphics/renderer.h"
#include <iostream>
#include <logger.h>
#include <GLFW/glfw3.h>

namespace Blocky {
	void Renderer::Clear(Vec3& skyColour)
	{
		// redraws the whole screen into the sky colour
		glClearColor(skyColour.x, skyColour.y, skyColour.z, 1.0f);
		// Clears the depth buffer and the colour buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/// <summary>
	/// Draws non index vertices bind all need varaibles
	/// count is the amount of triangles to draw
	/// </summary>
	/// <param name="vertex"></param>
	/// <param name="shader"></param>
	/// <param name="count"></param>
	void Renderer::DrawArray(VertexArray& vertex, Shader& shader, uint32_t count)
	{
		shader.Bind();
		vertex.Bind();
		glDrawArrays(GL_TRIANGLES, 0, count);
		vertex.UnBind();
		shader.UnBind();
	}

	void Renderer::NewFrame(Window* win)
	{
		// swaps the buffer from the active to resreve
		glfwSwapBuffers(win->window);
		// Gets all window events such as mount and keybaord input
		glfwPollEvents();
	}

	/// <summary>
	/// Draws indexed vertices and binds all needed methods
	/// Asssumes data is in 32bit form
	/// </summary>
	/// <param name="vertex"></param>
	/// <param name="index"></param>
	/// <param name="shader"></param>
	void Renderer::DrawElements(VertexArray& vertex, IndexBuffer& index, Shader& shader)
	{
		shader.Bind();
		vertex.Bind();
		index.Bind();
		// Draws the indices to the screen
		glDrawElements(GL_TRIANGLES, index.GetCount(), GL_UNSIGNED_INT, nullptr);
		shader.UnBind();
		vertex.UnBind();
		index.UnBind();
	}
}