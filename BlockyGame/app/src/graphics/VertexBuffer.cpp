#include "graphics/VertexBuffer.h"
#include "glad/glad.h"
#include <logger.h>
#include <stdio.h>
#include <graphics/renderer.h>

namespace Blocky {
	void VertexBuffer::Create(const void* data, uint32_t size)
	{
		// Creates a buffer on the gpu
		glCreateBuffers(1, &id);
		// Binds the buffer as an array buffer
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Sets that the data will be static as no data will be often changed
		// fills the buffer with the given data
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::CreateEmpty(uint32_t size, GLenum type)
	{
		// Creates the buffer
		glCreateBuffers(1, &id);
		// Binds the buffer onto the gpu
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Binds the buffer with null data
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, NULL, type);
	}

	void VertexBuffer::AddedData(const void* data, uint32_t size)
	{
		// Adds the given data to the active buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	VertexBuffer::~VertexBuffer()
	{
		// Deletes the current buffer
		glDeleteBuffers(1, &id);
	}

	void VertexBuffer::Bind()
	{
		// Binds the current buffer on the gpu
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::UnBind()
	{
		// unbinds the buffer by setting the binded buffer to be the null buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}