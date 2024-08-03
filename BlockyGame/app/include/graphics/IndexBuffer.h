#pragma once
#include <cstdint>
#include <algorithm>

namespace Blocky {

	class IndexBuffer
	{
	private:
		uint32_t id;
		uint32_t count;
	public:
		IndexBuffer() : id(0) {}
		~IndexBuffer();

		void Create(uint32_t* data, uint32_t m_Count);

		IndexBuffer(IndexBuffer&& rhs) noexcept
		{
			std::swap(id, rhs.id);
			std::swap(count, rhs.count);
		}

		IndexBuffer& operator=(IndexBuffer&& rhs) noexcept {
			std::swap(id, rhs.id);
			std::swap(count, rhs.count);
			return *this;
		}
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		void Bind();
		void UnBind();

		inline uint32_t GetCount() { return count; }
	};
}