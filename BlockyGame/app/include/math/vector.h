#pragma once
/**
 * Two component vector class
**/

#include <iostream>
namespace Blocky {
	class Vec2
	{
	public:
		float x;
		float y;
		/// Init Vec2 to 0,0
		Vec2();
		/// Init Vec2 to given vec2 values
		Vec2(const Vec2& vector);

		/**
		* 	Init Vec2 to given float
		*	\param float x \param float y
		**/
		Vec2(float value);

		/**
		* 	Init Vec2 to given float
		*	\param float x \param float y
		**/
		Vec2(float _x, float _y);

		~Vec2() {};


		Vec2 operator+(const Vec2& v) {
			Vec2 temp(0.0f);
			temp.x = x + v.x;
			temp.y = y + v.y;
			return temp;
		}
		Vec2 operator-(const Vec2& v) {
			Vec2 temp(0.0f);
			temp.x = x - v.x;
			temp.y = y - v.y;
			return temp;
		}
		Vec2 operator*(const float m) {
			Vec2 temp(0.0f);
			temp.x = x * m;
			temp.y = y * m;
			return temp;
		}
		Vec2 operator+(const float m) {
			Vec2 temp(0.0f);
			temp.x = x + m;
			temp.y = y + m;
			return temp;
		}
		//...

		bool operator < (const Vec2& rhs) const {
			return std::tie(x, y) < std::tie(rhs.x, rhs.y);
		}

		/**
		* 	Changes vector values to those given
		*	\param float x \param float y
		**/
		void Set(float _x, float _y);

		/**
		* 	Return x value
		*	\return float x
		**/
		float X() { return x; }

		/**
		* 	Return y value
		*	\return float y
		**/
		float Y() { return y; }

		bool operator() (Vec2 v1, Vec2 v2) const
		{
			return v1.x == v2.x &&
				v1.y == v2.y;
		}
	};

	/**
	 * Three component vector class
	**/
	class Vec3
	{
	public:
		float x;
		float y;
		float z;
		/// Init Vec3 to 0,0,0
		Vec3();
		/// Init Vec3 to given vec3 values
		Vec3(const Vec3& vector);
		/**
		* 	Init Vec3 to given float
		*	\param float x \param float y
		**/
		Vec3(float value);

		/**
		* 	Init Vec3 to given float
		*	\param float x \param float y
		**/
		Vec3(float _x, float _y, float _z);

		~Vec3() {};


		bool operator==(const Vec3 v) {
			return (v.x == x) && (v.y == y) && (v.z == z);
		}
		Vec3 operator+(const Vec3& v) {
			Vec3 temp(0.0f);
			temp.x = x + v.x;
			temp.y = y + v.y;
			temp.z = z + v.z;
			return temp;
		}
		Vec3 operator-(const Vec3& v) {
			Vec3 temp(0.0f);
			temp.x = x - v.x;
			temp.y = y - v.y;
			temp.z = z - v.z;
			return temp;
		}
		Vec3 operator*(const Vec3& v) {
			Vec3 temp(0.0f);
			temp.x = x * v.x;
			temp.y = y * v.y;
			temp.z = z * v.z;
			return temp;
		}
		Vec3 operator/(const Vec3& v) {
			Vec3 temp(0.0f);
			temp.x = x / v.x;
			temp.y = y / v.y;
			temp.z = z / v.z;
			return temp;
		}

		Vec3 operator+(const float v) {
			Vec3 temp(0.0f);
			temp.x = x + v;
			temp.y = y + v;
			temp.z = z + v;
			return temp;
		}
		Vec3 operator-(const float v) {
			Vec3 temp(0.0f);
			temp.x = x - v;
			temp.y = y - v;
			temp.z = z - v;
			return temp;
		}
		Vec3 operator*(const float v) {
			Vec3 temp(0.0f);
			temp.x = x * v;
			temp.y = y * v;
			temp.z = z * v;
			return temp;
		}
		Vec3 operator/(const float v) {
			Vec3 temp(0.0f);
			temp.x = x / v;
			temp.y = y / v;
			temp.z = z / v;
			return temp;
		}
		bool operator() (Vec3 v1, Vec3 v2) const
		{
			return v1.x == v2.x &&
				v1.y == v2.y &&
				v1.z == v2.z;
		}
		bool operator < (const Vec3& rhs) const {
			return std::tie(x, y, z) < std::tie(rhs.x, rhs.y, rhs.z);
		}
		/**
		* 	Changes vector values to those given
		*	\param float x \param float y \param float z
		**/
		void Set(float _x, float _y, float _z);

		/**
		* 	Return x value
		*	\return float x
		**/
		float X() { return x; }

		/**
		* 	Return y value
		*	\return float y
		**/
		float Y() { return y; }

		/**
		* 	Return z value
		*	\return float z
		**/
		float Z() { return z; }
	};

	/**
	 * Three component vector class
	**/
	class Vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;
		/// Init Vec3 to 0,0,0,0
		Vec4();
		/// Init Vec3 to given vec3 values
		Vec4(const Vec4& vector);

		/**
		* 	Init Vec4 to given float for all values
		*	\param value
		**/
		Vec4(float value);
		/**
		* 	Init Vec3 to given float
		*	\param float x \param float y
		**/
		Vec4(float _x, float _y, float _z, float _w);

		~Vec4() {};

		/**
		* 	Changes vector values to those given
		*	\param float x \param float y \param float z \param float w
		**/
		void Set(float _x, float _y, float _z, float _w);

		/**
		* 	Return x value
		*	\return float x
		**/
		float X() { return x; }

		/**
		* 	Return y value
		*	\return float y
		**/
		float Y() { return y; }

		/**
		* 	Return z value
		*	\return float z
		**/
		float Z() { return z; }

		/**
		* 	Return W value
		*	\return float w
		**/
		float W() { return w; }
	};


	class Vector
	{

	public:
		static float DotProduct(Vec2& v1, Vec2& v2);
		static float DotProduct(Vec3& v1, Vec3& v2);
		static float DotProduct(Vec4& v1, Vec4& v2);

		static Vec3 CrossProduct(Vec3& v1, Vec3& v2);

		//Basic Vec2 methods

		static inline Vec2 Add(Vec2& v1, Vec2& v2) { return Vec2(v1.X() + v2.X(), v1.Y() + v2.Y()); }
		static inline Vec2 Sub(Vec2& v1, Vec2& v2) { return Vec2(v1.X() - v2.X(), v1.Y() - v2.Y()); }
		static inline Vec2 Mul(Vec2& v1, Vec2& v2) { return Vec2(v1.X() * v2.X(), v1.Y() * v2.Y()); }
		static inline Vec2 Div(Vec2& v1, Vec2& v2) { return Vec2(v1.X() / v2.X(), v1.Y() / v2.Y()); }

		//Basic Vec3 methods

		static inline Vec3 Add(Vec3& v1, Vec3& v2) { return Vec3(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z()); }
		static inline Vec3 Sub(Vec3& v1, Vec3& v2) { return Vec3(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z()); }
		static inline Vec3 Mul(Vec3& v1, Vec3& v2) { return Vec3(v1.X() * v2.X(), v1.Y() * v2.Y(), v1.Z() * v2.Z()); }
		static inline Vec3 Div(Vec3& v1, Vec3& v2) { return Vec3(v1.X() / v2.X(), v1.Y() / v2.Y(), v1.Z() / v2.Z()); }
		static inline Vec3 Mult(Vec3& v1, float n) { return Vec3(v1.X() * n, v1.Y() * n, v1.Z() * n); }

		//Basic Vec4 methods
		static inline Vec4 Add(Vec4& v1, Vec4& v2) { return Vec4(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z(), v1.W() + v2.W()); }
		static inline Vec4 Sub(Vec4& v1, Vec4& v2) { return Vec4(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z(), v1.W() - v2.W()); }
		static inline Vec4 Mul(Vec4& v1, Vec4& v2) { return Vec4(v1.X() * v2.X(), v1.Y() * v2.Y(), v1.Z() * v2.Z(), v1.W() * v2.W()); }
		static inline Vec4 Div(Vec4& v1, Vec4& v2) { return Vec4(v1.X() / v2.X(), v1.Y() / v2.Y(), v1.Z() / v2.Z(), v1.W() / v2.W()); }

		// SqaureLength
		static float SqaureLength(Vec2& v);
		static float SqaureLength(Vec3& v);
		static float SqaureLength(Vec4& v);

		// Magnitude
		static float Magnitude(Vec2& v);
		static float Magnitude(Vec3& v);
		static float Magnitude(Vec4& v);

		static Vec2 Normilise(Vec2& v);
		static Vec3 Normilise(Vec3& v);
		static Vec4 Normilise(Vec4& v);
	};
}