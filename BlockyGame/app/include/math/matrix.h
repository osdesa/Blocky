#pragma once
#include "math/vector.h"

namespace Blocky {


    class Matrix4x4
    {
    public:
        float v[16];

        Matrix4x4();
        Matrix4x4(float vals[16]);
        Matrix4x4(float value);

        void StripTranslation();

        float GetValue2D(int row, int col);
        void Display();
    };

    class Matrix2x2
    {
    public:
        float v[4];

        Matrix2x2();
        Matrix2x2(float f1, float f2, float f3, float f4);
        Matrix2x2(float vals[4]);
        Matrix2x2(Matrix2x2& m);
        Matrix2x2(float value);

        float GetValue2D(int row, int col);
        void Display();
    };

    class Matrix
    {
    public:
        //Matrix(const Matrix4x4& obj);

        static Matrix4x4 Translate(Vec3& vec);
        static Matrix4x4 Translate(Vec4& vec);

        static Matrix4x4 Translate(Matrix4x4& mat, Vec3& vec);
        static Matrix4x4 Translate(Matrix4x4& mat, Vec4& vec);

        static Matrix4x4 Transpose(Matrix4x4& mat);

        static Matrix4x4 Mult(Matrix4x4& l, Matrix4x4& r);
        static Matrix4x4 Mult(const Matrix4x4& l, const Matrix4x4& r);
        static Matrix4x4 Mult(const Matrix4x4& l, Matrix4x4& r);
        static Matrix4x4 Mult(Matrix4x4& l, const Matrix4x4& r);

        static Matrix4x4 Scale(Matrix4x4& mat, Vec3 scale);
        static Matrix4x4 Scale(Vec3 scale);
        static Matrix4x4 Rotate(float angle, Vec3& vec);
        static Matrix4x4 Rotate(Matrix4x4& mat, float angle, Vec3 vec);
        static Vec4      Transform(Matrix4x4& mat, Vec4& vec);
        static Matrix4x4 LookAt(Vec3 Eye, Vec3 Center, Vec3 Up);
        static Matrix4x4 Perspective(float fovy, float aspect, float near, float far);
        static Matrix4x4 Orthographic(float left, float right, float bottom, float top);

        static Matrix2x2 Mult(Matrix2x2& l, Matrix2x2& r);
    };
}