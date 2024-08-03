#pragma once

#include "external/FastNoiseLite.h"
#include <map>
#include <math/vector.h>

namespace Blocky {
	class NoiseGen
	{
	public:
		static int GetHeight(int x, int z, FastNoiseLite noise, std::map<Vec2, int>& heights)
		{
			int maxHeight = 0;
			Vec2 loc = Vec2(x, z);
			if (heights.find(loc) == heights.end()) {
				// not cached yet
				maxHeight = floor(40 + noise.GetNoise((float)x, (float)z) * 35);
				heights[loc] = maxHeight;
			}
			else {
				maxHeight = heights[loc];
			}
			return maxHeight;
		}
	};
}