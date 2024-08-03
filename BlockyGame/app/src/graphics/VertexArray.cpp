#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include <logger.h>

namespace Blocky {
	VertexArray::VertexArray()
	{

	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void VertexArray::Create()
	{
		glGenVertexArrays(1, &vao);
	}

	void VertexArray::AddBuffer(VertexBuffer& vb, VBLayout& layout)
	{
		// binds the buffers making them active
		Bind();
		vb.Bind();
		// Gets all the elements of the vao eg if a vec2 and vec3 are being sent
		auto& elements = layout.GetElements();
		uint32_t offset = 0;
		for (uint32_t i = 0; i < elements.size(); i++) {
			// Gets the current element
			auto element = elements[i];
			// tells openGL that this vertex array at this point has is going to be set
			glEnableVertexAttribArray(i);
			// tells openGL at a posistion the element infomation
			glVertexAttribPointer(i, element.count, element.type,
				element.normilized, layout.GetStrite(), (const void*)offset);

			// increase the offset by calulating the size of the type
			offset += element.count * VBLayout::GetSize(element.type);
		}
	}


	void VertexArray::Bind()
	{
		glBindVertexArray(vao);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}
}