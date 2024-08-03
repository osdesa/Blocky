#pragma once
#include "BMath.h"

namespace Blocky {
	class VectorBase
	{

	public:
		float DotProduct(Vec2& v1, Vec2& v2);
		float DotProduct(Vec3& v1, Vec3& v2);
		float DotProduct(Vec4& v1, Vec4& v2);

		Vec3 CrossProduct(Vec3& v1, Vec3& v2);

		//Basic Vec2 methods

		inline Vec2 Add(Vec2& v1, Vec2& v2) { return Vec2(v1.X() + v2.X(), v1.Y() + v2.Y()); }
		inline Vec2 Sub(Vec2& v1, Vec2& v2) { return Vec2(v1.X() - v2.X(), v1.Y() - v2.Y()); }
		inline Vec2 Mul(Vec2& v1, Vec2& v2) { return Vec2(v1.X() * v2.X(), v1.Y() * v2.Y()); }
		inline Vec2 Div(Vec2& v1, Vec2& v2) { return Vec2(v1.X() / v2.X(), v1.Y() / v2.Y()); }

		//Basic Vec3 methods

		inline Vec3 Add(Vec3& v1, Vec3& v2) { return Vec3(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z()); }
		inline Vec3 Sub(Vec3& v1, Vec3& v2) { return Vec3(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z()); }
		inline Vec3 Mul(Vec3& v1, Vec3& v2) { return Vec3(v1.X() * v2.X(), v1.Y() * v2.Y(), v1.Z() * v2.Z()); }
		inline Vec3 Div(Vec3& v1, Vec3& v2) { return Vec3(v1.X() / v2.X(), v1.Y() / v2.Y(), v1.Z() / v2.Z()); }
		inline Vec3 Mult(Vec3& v1, float n) { return Vec3(v1.X() * n, v1.Y() * n, v1.Z() * n); }

		//Basic Vec4 methods
		inline Vec4 Add(Vec4& v1, Vec4& v2) { return Vec4(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z(), v1.W() + v2.W()); }
		inline Vec4 Sub(Vec4& v1, Vec4& v2) { return Vec4(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z(), v1.W() - v2.W()); }
		inline Vec4 Mul(Vec4& v1, Vec4& v2) { return Vec4(v1.X() * v2.X(), v1.Y() * v2.Y(), v1.Z() * v2.Z(), v1.W() * v2.W()); }
		inline Vec4 Div(Vec4& v1, Vec4& v2) { return Vec4(v1.X() / v2.X(), v1.Y() / v2.Y(), v1.Z() / v2.Z(), v1.W() / v2.W()); }

		// SqaureLength
		float SqaureLength(Vec2& v);
		float SqaureLength(Vec3& v);
		float SqaureLength(Vec4& v);

		// Magnitude
		float Magnitude(Vec2& v);
		float Magnitude(Vec3& v);
		float Magnitude(Vec4& v);

		Vec2 Normilise(Vec2& v);
		Vec3 Normilise(Vec3& v);
		Vec4 Normilise(Vec4& v);
	};
}