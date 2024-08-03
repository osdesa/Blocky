#include "math/vector.h"
#include "logger.h"

// Needed for sqrt
#include <cmath>

namespace Blocky {
    // Main Vector methods
    float Vector::DotProduct(Vec2& v1, Vec2& v2)
    {
        return (float)(v1.x * v2.x) + (v1.y * v2.y);
    }
    float Vector::DotProduct(Vec3& v1, Vec3& v2)
    {
        return (float)(v1.x * v2.x) + (v1.y * v2.y) + (v1.Z() * v2.Z());
    }
    float Vector::DotProduct(Vec4& v1, Vec4& v2)
    {
        return (float)(v1.x * v2.x) + (v1.y * v2.y) + (v1.Z() * v2.Z()) + (v1.W() * v2.W());
    }

    Vec3 Vector::CrossProduct(Vec3& v1, Vec3& v2)
    {
        return Vec3(
            (v1.y * v2.Z()) - (v1.Z() * v2.y),
            (v1.Z() * v2.x) - (v1.x * v2.Z()),
            (v1.x * v2.y) - (v1.y * v2.x)
        );
    }

    float Vector::SqaureLength(Vec2& v)
    {
        return ((v.x * v.x) + (v.y * v.y));
    }
    float Vector::SqaureLength(Vec3& v)
    {
        return ((v.x * v.x) + (v.y * v.y) + (v.Z() * v.Z()));
    }
    float Vector::SqaureLength(Vec4& v)
    {
        return ((v.x * v.x) + (v.y * v.y)
            + (v.Z() * v.Z()) + (v.W() * v.W()));
    }

    float Vector::Magnitude(Vec2& v)
    {
        return (float)sqrt(SqaureLength(v));
    }
    float Vector::Magnitude(Vec3& v)
    {
        return (float)sqrt(SqaureLength(v));
    }
    float Vector::Magnitude(Vec4& v)
    {
        return (float)sqrt(SqaureLength(v));
    }

    Vec2 Vector::Normilise(Vec2& v)
    {
        float oneOverMag = 1.0f / Magnitude(v);
        return Vec2(v.x * oneOverMag,
            v.y * oneOverMag);
    }
    Vec3 Vector::Normilise(Vec3& v)
    {
        float oneOverMag = 1.0f / Magnitude(v);
        return Vec3(v.x * oneOverMag,
            v.y * oneOverMag,
            v.Z() * oneOverMag);
    }
    Vec4 Vector::Normilise(Vec4& v)
    {
        float oneOverMag = 1.0f / Magnitude(v);
        return Vec4(v.x * oneOverMag,
            v.y * oneOverMag,
            v.Z() * oneOverMag,
            v.W() * oneOverMag);
    }

    // Vec2 Start
    Vec2::Vec2()
        : x(0.0f), y(0.0f)
    {

    }

    Vec2::Vec2(const Vec2& vector)
        : x(vector.x), y(vector.y)
    {

    }

    Vec2::Vec2(float value)
        : x(value), y(value)
    {

    }

    Vec2::Vec2(float _x, float _y)
        : x(_x), y(_y)
    {

    }

    void Vec2::Set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    // Vec2 End


    // Vec3 Start
    Vec3::Vec3()
        : x(0.0f), y(0.0f), z(0.0f)
    {

    }

    Vec3::Vec3(const Vec3& vector)
        : x(vector.x), y(vector.y), z(vector.z)
    {

    }

    Vec3::Vec3(float value)
        : x(value), y(value), z(value)
    {

    }

    Vec3::Vec3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {

    }

    void Vec3::Set(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    // Vec3 End


    // Vec4 Start
    Vec4::Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {

    }

    Vec4::Vec4(const Vec4& vector)
        : x(vector.x), y(vector.y), z(vector.z), w(vector.w)
    {

    }

    Vec4::Vec4(float value)
        : x(value), y(value), z(value), w(value)
    {

    }

    Vec4::Vec4(float _x, float _y, float _z, float _w)
        : x(_x), y(_y), z(_z), w(_w)
    {

    }

    void Vec4::Set(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
    // Vec4 End
}