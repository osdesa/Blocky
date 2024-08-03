#pragma once

#include "VertexBuffer.h"
#include "VBLayout.h"
#include "glad/glad.h"
#include "logger.h"

namespace Blocky {
	class VertexArray
	{
	private:
		uint32_t vao;
	public:
		VertexArray();
		~VertexArray();

		VertexArray(VertexArray&& rhs) noexcept
		{
			std::swap(vao, rhs.vao);
		}
		VertexArray& operator=(VertexArray&& rhs) noexcept {
			std::swap(vao, rhs.vao);
			return *this;
		}
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void Create();

		void UnBind();
		void Bind();
		void AddBuffer(VertexBuffer& vb, VBLayout& layout);

		uint32_t GetId() { return vao; }
	};
}