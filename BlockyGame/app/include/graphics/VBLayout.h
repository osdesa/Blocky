#pragma once
#include <vector>

namespace Blocky {
	struct VBElement
	{
		uint32_t type;
		uint32_t count;
		unsigned char normilized;
	};

	class VBLayout
	{
	public:
		VBLayout();
		~VBLayout();

		void Push(uint32_t type, uint32_t count, bool normalized);


		static uint32_t GetSize(uint32_t type);
		inline std::vector<VBElement>& GetElements() { return elements; }
		inline uint32_t GetStrite() { return stride; }

	private:
		std::vector<VBElement> elements;
		uint32_t stride;
	};
}