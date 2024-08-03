#pragma once
#include <cstdint>
#include <algorithm>
#include "glad/glad.h"
#include "logger.h"

namespace Blocky {

	class VertexBuffer
	{
	private:
		uint32_t id;
	public:
		VertexBuffer() = default;
		void Create(const void* data, uint32_t size);
		void CreateEmpty(uint32_t size, GLenum type);
		void AddedData(const void* data, uint32_t size);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer& operator=(VertexBuffer&& rhs) noexcept {
			std::swap(id, rhs.id);
			return *this;
		}
		VertexBuffer(VertexBuffer&& rhs) noexcept
		{
			std::swap(id, rhs.id);
		}


		void Bind();
		void UnBind();
	};
}