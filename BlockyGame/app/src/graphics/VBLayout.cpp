#include "graphics/VBLayout.h"
#include "glad/glad.h"
#include "logger.h"

namespace Blocky {
	VBLayout::VBLayout()
		: stride(0)
	{
	}

	VBLayout::~VBLayout()
	{
	}

	uint32_t VBLayout::GetSize(uint32_t type)
	{
		// Converts the type such as float to its byte size eg float = 4 bytes
		uint32_t size = 0;
		switch (type)
		{
		case GL_FLOAT:
			size += 4;
			break;
		case GL_UNSIGNED_INT:
			size += 4;
			break;
		case GL_BYTE:
			size += 1;
			break;
		default:
			// Very bad
			break;
		}
		return size;
	}

	void VBLayout::Push(uint32_t type, uint32_t count, bool normalized)
	{
		// addes the given values to the elements vector
		elements.push_back({ type, count, normalized });
		// Increase the distance between new blocks of data by the calulated 
		//size of the type and the number of values
		stride += count * GetSize(type);

	}
}