#pragma once

#include "vector.h"
#include "matrix.h"
#include "math.h"
#include "Graphics.h"


#define DEG_TO_RAD(DEG) (DEG * RADCONST)

namespace Blocky {
	const double PI = 3.141592653589793238462643383279;
	const double TWOPI = 2 * PI;
	const double HALFPI = PI / 2;
	const double QUARTARPI = PI / 4;

	const double RADCONST = PI / 180;

	struct Vertex
	{
		Vec3 posistion;
		Vec3 colour;
		Vec3 normal;
		Vec2 uv;
	};
}
