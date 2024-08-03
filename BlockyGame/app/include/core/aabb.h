#pragma once
#include <math/vector.h>

namespace Blocky {
	class AABB
	{
	public:
		static bool collide(AABB a, AABB b);
		inline void Update(Vec3 newMin, Vec3 newMax) { min = newMin; max = newMax; }
		inline Vec3 GetMin() { return min; }
		inline Vec3 GetMax() { return max; }
	private:
		Vec3 min;
		Vec3 max;
	};
}