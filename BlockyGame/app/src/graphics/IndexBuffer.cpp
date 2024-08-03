#include "graphics/IndexBuffer.h"
#include "glad/glad.h"
#include <logger.h>

namespace Blocky {
	void IndexBuffer::Create(uint32_t* data, uint32_t m_Count)
	{
		// sets the amount of vertices and stores for later use
		count = m_Count;
		// Creates a buffer
		glCreateBuffers(1, &id);
		// Makes the buffer an element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		// Binds the buffer with the supplied data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void IndexBuffer::Bind()
	{
		// makes this buffer the active one
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void IndexBuffer::UnBind()
	{
		// set the active buffer to an empty one removing this as being set
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}