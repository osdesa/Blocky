#include "math/matrix.h"
#include <cstring>
#include "math.h"
#include <logger.h>

namespace Blocky {
    Matrix4x4 Matrix::Transpose(Matrix4x4& mat)
    {
        Matrix4x4 transpose;
        //Row 1
        transpose.v[0] = mat.v[0];
        transpose.v[1] = mat.v[4];
        transpose.v[2] = mat.v[8];
        transpose.v[3] = mat.v[12];
        //Row 2
        transpose.v[4] = mat.v[1];
        transpose.v[5] = mat.v[5];
        transpose.v[6] = mat.v[9];
        transpose.v[7] = mat.v[13];
        //Row 3
        transpose.v[8] = mat.v[2];
        transpose.v[9] = mat.v[6];
        transpose.v[10] = mat.v[10];
        transpose.v[11] = mat.v[14];
        //Row 4
        transpose.v[12] = mat.v[3];
        transpose.v[13] = mat.v[7];
        transpose.v[14] = mat.v[11];
        transpose.v[15] = mat.v[15];

        return transpose;
    }

    // Takes in two 4x4 matrixs and does left x right 
    // returns a 4x4 matrix
    Matrix4x4 Matrix::Mult(Matrix4x4& l, Matrix4x4& r)
    {
        Matrix4x4 mult;
        mult.v[0] = (l.v[0] * r.v[0]) + (l.v[1] * r.v[4]) + (l.v[2] * r.v[8]) + (l.v[3] * r.v[12]);
        mult.v[1] = (l.v[0] * r.v[1]) + (l.v[1] * r.v[5]) + (l.v[2] * r.v[9]) + (l.v[3] * r.v[13]);
        mult.v[2] = (l.v[0] * r.v[2]) + (l.v[1] * r.v[6]) + (l.v[2] * r.v[10]) + (l.v[3] * r.v[14]);
        mult.v[3] = (l.v[0] * r.v[3]) + (l.v[1] * r.v[7]) + (l.v[2] * r.v[11]) + (l.v[3] * r.v[15]);

        mult.v[4] = (l.v[4] * r.v[0]) + (l.v[5] * r.v[4]) + (l.v[6] * r.v[8]) + (l.v[7] * r.v[12]);
        mult.v[5] = (l.v[4] * r.v[1]) + (l.v[5] * r.v[5]) + (l.v[6] * r.v[9]) + (l.v[7] * r.v[13]);
        mult.v[6] = (l.v[4] * r.v[2]) + (l.v[5] * r.v[6]) + (l.v[6] * r.v[10]) + (l.v[7] * r.v[14]);
        mult.v[7] = (l.v[4] * r.v[3]) + (l.v[5] * r.v[7]) + (l.v[6] * r.v[11]) + (l.v[7] * r.v[15]);

        mult.v[8] = (l.v[8] * r.v[0]) + (l.v[9] * r.v[4]) + (l.v[10] * r.v[8]) + (l.v[11] * r.v[12]);
        mult.v[9] = (l.v[8] * r.v[1]) + (l.v[9] * r.v[5]) + (l.v[10] * r.v[9]) + (l.v[11] * r.v[13]);
        mult.v[10] = (l.v[8] * r.v[2]) + (l.v[9] * r.v[6]) + (l.v[10] * r.v[10]) + (l.v[11] * r.v[14]);
        mult.v[11] = (l.v[8] * r.v[3]) + (l.v[9] * r.v[7]) + (l.v[10] * r.v[11]) + (l.v[11] * r.v[15]);

        mult.v[12] = (l.v[12] * r.v[0]) + (l.v[13] * r.v[4]) + (l.v[14] * r.v[8]) + (l.v[15] * r.v[12]);
        mult.v[13] = (l.v[12] * r.v[1]) + (l.v[13] * r.v[5]) + (l.v[14] * r.v[9]) + (l.v[15] * r.v[13]);
        mult.v[14] = (l.v[12] * r.v[2]) + (l.v[13] * r.v[6]) + (l.v[14] * r.v[10]) + (l.v[15] * r.v[14]);
        mult.v[15] = (l.v[12] * r.v[3]) + (l.v[13] * r.v[7]) + (l.v[14] * r.v[11]) + (l.v[15] * r.v[15]);

        return mult;
    }

    Matrix4x4 Matrix::Mult(const Matrix4x4& l, const Matrix4x4& r)
    {
        Matrix4x4 mult;
        mult.v[0] = (l.v[0] * r.v[0]) + (l.v[1] * r.v[4]) + (l.v[2] * r.v[8]) + (l.v[3] * r.v[12]);
        mult.v[1] = (l.v[0] * r.v[1]) + (l.v[1] * r.v[5]) + (l.v[2] * r.v[9]) + (l.v[3] * r.v[13]);
        mult.v[2] = (l.v[0] * r.v[2]) + (l.v[1] * r.v[6]) + (l.v[2] * r.v[10]) + (l.v[3] * r.v[14]);
        mult.v[3] = (l.v[0] * r.v[3]) + (l.v[1] * r.v[7]) + (l.v[2] * r.v[11]) + (l.v[3] * r.v[15]);

        mult.v[4] = (l.v[4] * r.v[0]) + (l.v[5] * r.v[4]) + (l.v[6] * r.v[8]) + (l.v[7] * r.v[12]);
        mult.v[5] = (l.v[4] * r.v[1]) + (l.v[5] * r.v[5]) + (l.v[6] * r.v[9]) + (l.v[7] * r.v[13]);
        mult.v[6] = (l.v[4] * r.v[2]) + (l.v[5] * r.v[6]) + (l.v[6] * r.v[10]) + (l.v[7] * r.v[14]);
        mult.v[7] = (l.v[4] * r.v[3]) + (l.v[5] * r.v[7]) + (l.v[6] * r.v[11]) + (l.v[7] * r.v[15]);

        mult.v[8] = (l.v[8] * r.v[0]) + (l.v[9] * r.v[4]) + (l.v[10] * r.v[8]) + (l.v[11] * r.v[12]);
        mult.v[9] = (l.v[8] * r.v[1]) + (l.v[9] * r.v[5]) + (l.v[10] * r.v[9]) + (l.v[11] * r.v[13]);
        mult.v[10] = (l.v[8] * r.v[2]) + (l.v[9] * r.v[6]) + (l.v[10] * r.v[10]) + (l.v[11] * r.v[14]);
        mult.v[11] = (l.v[8] * r.v[3]) + (l.v[9] * r.v[7]) + (l.v[10] * r.v[11]) + (l.v[11] * r.v[15]);

        mult.v[12] = (l.v[12] * r.v[0]) + (l.v[13] * r.v[4]) + (l.v[14] * r.v[8]) + (l.v[15] * r.v[12]);
        mult.v[13] = (l.v[12] * r.v[1]) + (l.v[13] * r.v[5]) + (l.v[14] * r.v[9]) + (l.v[15] * r.v[13]);
        mult.v[14] = (l.v[12] * r.v[2]) + (l.v[13] * r.v[6]) + (l.v[14] * r.v[10]) + (l.v[15] * r.v[14]);
        mult.v[15] = (l.v[12] * r.v[3]) + (l.v[13] * r.v[7]) + (l.v[14] * r.v[11]) + (l.v[15] * r.v[15]);

        return mult;
    }

    Matrix4x4 Matrix::Mult(const Matrix4x4& l, Matrix4x4& r)
    {
        Matrix4x4 mult;
        mult.v[0] = (l.v[0] * r.v[0]) + (l.v[1] * r.v[4]) + (l.v[2] * r.v[8]) + (l.v[3] * r.v[12]);
        mult.v[1] = (l.v[0] * r.v[1]) + (l.v[1] * r.v[5]) + (l.v[2] * r.v[9]) + (l.v[3] * r.v[13]);
        mult.v[2] = (l.v[0] * r.v[2]) + (l.v[1] * r.v[6]) + (l.v[2] * r.v[10]) + (l.v[3] * r.v[14]);
        mult.v[3] = (l.v[0] * r.v[3]) + (l.v[1] * r.v[7]) + (l.v[2] * r.v[11]) + (l.v[3] * r.v[15]);

        mult.v[4] = (l.v[4] * r.v[0]) + (l.v[5] * r.v[4]) + (l.v[6] * r.v[8]) + (l.v[7] * r.v[12]);
        mult.v[5] = (l.v[4] * r.v[1]) + (l.v[5] * r.v[5]) + (l.v[6] * r.v[9]) + (l.v[7] * r.v[13]);
        mult.v[6] = (l.v[4] * r.v[2]) + (l.v[5] * r.v[6]) + (l.v[6] * r.v[10]) + (l.v[7] * r.v[14]);
        mult.v[7] = (l.v[4] * r.v[3]) + (l.v[5] * r.v[7]) + (l.v[6] * r.v[11]) + (l.v[7] * r.v[15]);

        mult.v[8] = (l.v[8] * r.v[0]) + (l.v[9] * r.v[4]) + (l.v[10] * r.v[8]) + (l.v[11] * r.v[12]);
        mult.v[9] = (l.v[8] * r.v[1]) + (l.v[9] * r.v[5]) + (l.v[10] * r.v[9]) + (l.v[11] * r.v[13]);
        mult.v[10] = (l.v[8] * r.v[2]) + (l.v[9] * r.v[6]) + (l.v[10] * r.v[10]) + (l.v[11] * r.v[14]);
        mult.v[11] = (l.v[8] * r.v[3]) + (l.v[9] * r.v[7]) + (l.v[10] * r.v[11]) + (l.v[11] * r.v[15]);

        mult.v[12] = (l.v[12] * r.v[0]) + (l.v[13] * r.v[4]) + (l.v[14] * r.v[8]) + (l.v[15] * r.v[12]);
        mult.v[13] = (l.v[12] * r.v[1]) + (l.v[13] * r.v[5]) + (l.v[14] * r.v[9]) + (l.v[15] * r.v[13]);
        mult.v[14] = (l.v[12] * r.v[2]) + (l.v[13] * r.v[6]) + (l.v[14] * r.v[10]) + (l.v[15] * r.v[14]);
        mult.v[15] = (l.v[12] * r.v[3]) + (l.v[13] * r.v[7]) + (l.v[14] * r.v[11]) + (l.v[15] * r.v[15]);

        return mult;
    }
    Matrix4x4 Matrix::Mult(Matrix4x4& l, const Matrix4x4& r)
    {
        Matrix4x4 mult;
        mult.v[0] = (l.v[0] * r.v[0]) + (l.v[1] * r.v[4]) + (l.v[2] * r.v[8]) + (l.v[3] * r.v[12]);
        mult.v[1] = (l.v[0] * r.v[1]) + (l.v[1] * r.v[5]) + (l.v[2] * r.v[9]) + (l.v[3] * r.v[13]);
        mult.v[2] = (l.v[0] * r.v[2]) + (l.v[1] * r.v[6]) + (l.v[2] * r.v[10]) + (l.v[3] * r.v[14]);
        mult.v[3] = (l.v[0] * r.v[3]) + (l.v[1] * r.v[7]) + (l.v[2] * r.v[11]) + (l.v[3] * r.v[15]);

        mult.v[4] = (l.v[4] * r.v[0]) + (l.v[5] * r.v[4]) + (l.v[6] * r.v[8]) + (l.v[7] * r.v[12]);
        mult.v[5] = (l.v[4] * r.v[1]) + (l.v[5] * r.v[5]) + (l.v[6] * r.v[9]) + (l.v[7] * r.v[13]);
        mult.v[6] = (l.v[4] * r.v[2]) + (l.v[5] * r.v[6]) + (l.v[6] * r.v[10]) + (l.v[7] * r.v[14]);
        mult.v[7] = (l.v[4] * r.v[3]) + (l.v[5] * r.v[7]) + (l.v[6] * r.v[11]) + (l.v[7] * r.v[15]);

        mult.v[8] = (l.v[8] * r.v[0]) + (l.v[9] * r.v[4]) + (l.v[10] * r.v[8]) + (l.v[11] * r.v[12]);
        mult.v[9] = (l.v[8] * r.v[1]) + (l.v[9] * r.v[5]) + (l.v[10] * r.v[9]) + (l.v[11] * r.v[13]);
        mult.v[10] = (l.v[8] * r.v[2]) + (l.v[9] * r.v[6]) + (l.v[10] * r.v[10]) + (l.v[11] * r.v[14]);
        mult.v[11] = (l.v[8] * r.v[3]) + (l.v[9] * r.v[7]) + (l.v[10] * r.v[11]) + (l.v[11] * r.v[15]);

        mult.v[12] = (l.v[12] * r.v[0]) + (l.v[13] * r.v[4]) + (l.v[14] * r.v[8]) + (l.v[15] * r.v[12]);
        mult.v[13] = (l.v[12] * r.v[1]) + (l.v[13] * r.v[5]) + (l.v[14] * r.v[9]) + (l.v[15] * r.v[13]);
        mult.v[14] = (l.v[12] * r.v[2]) + (l.v[13] * r.v[6]) + (l.v[14] * r.v[10]) + (l.v[15] * r.v[14]);
        mult.v[15] = (l.v[12] * r.v[3]) + (l.v[13] * r.v[7]) + (l.v[14] * r.v[11]) + (l.v[15] * r.v[15]);

        return mult;
    }

    Vec4 Matrix::Transform(Matrix4x4& mat, Vec4& vec)
    {
        Vec4 rot;
        rot.x = (vec.x * mat.v[0]) + (vec.y * mat.v[4]) + (vec.z * mat.v[8]) + mat.v[12];
        rot.y = (vec.x * mat.v[1]) + (vec.y * mat.v[5]) + (vec.z * mat.v[9]) + mat.v[13];
        rot.z = (vec.x * mat.v[2]) + (vec.y * mat.v[6]) + (vec.z * mat.v[10]) + mat.v[14];
        rot.w = vec.w;
        return rot;
    }


    Matrix4x4 Matrix::Rotate(float angle, Vec3& vec)
    {
        float C = cos(angle);
        float S = sin(angle);

        Vec3 n = Vector::Normilise(vec);
        Vec3 temp = Vector::Mult(n, (1.0f - C));

        Matrix4x4 rotate;
        // top row
        rotate.v[0] = C + temp.x * n.x;
        rotate.v[1] = 0 + temp.x * n.y + S * n.z;
        rotate.v[2] = 0 + temp.x * n.z - S * n.y;

        // mid row
        rotate.v[4] = 0 + temp.y * n.x - S * n.z;
        rotate.v[5] = C + temp.y * n.y;
        rotate.v[6] = 0 + temp.y * n.z + S * n.x;

        // bottom but not
        rotate.v[8] = 0 + temp.z * n.x + S * n.y;
        rotate.v[9] = 0 + temp.z * n.y - S * n.x;
        rotate.v[10] = C + temp.z * n.z;

        return rotate;
    }

    Matrix4x4 Matrix::Rotate(Matrix4x4& mat, float angle, Vec3 vec)
    {
        float C = cos(angle);
        float S = sin(angle);

        Vec3 n = Vector::Normilise(vec);
        Vec3 temp = Vector::Mult(n, (1.0f - C));

        Matrix4x4 rotate;
        // top row
        rotate.v[0] = C + temp.x * n.x;
        rotate.v[1] = 0 + temp.x * n.y + S * n.z;
        rotate.v[2] = 0 + temp.x * n.z - S * n.y;

        // mid row
        rotate.v[4] = 0 + temp.y * n.x - S * n.z;
        rotate.v[5] = C + temp.y * n.y;
        rotate.v[6] = 0 + temp.y * n.z + S * n.x;

        // bottom but not
        rotate.v[8] = 0 + temp.z * n.x + S * n.y;
        rotate.v[9] = 0 + temp.z * n.y - S * n.x;
        rotate.v[10] = C + temp.z * n.z;

        return Matrix::Mult(mat, rotate);
    }

    Matrix4x4 Matrix::LookAt(Vec3 Eye, Vec3 Center, Vec3 Up)
    {
        Matrix4x4 m = Matrix4x4(0.0f);
        Vec3 x = Vec3();
        Vec3 y = Vec3();
        Vec3 z = Vec3();
        Vec3 temp = Vector::Sub(Eye, Center);

        z = Vector::Normilise(temp);
        temp = z;
        y = Up;

        x = Vector::CrossProduct(y, temp);
        y = Vector::CrossProduct(temp, x);

        x = Vector::Normilise(x);
        y = Vector::Normilise(y);

        m.v[0] = x.x;
        m.v[4] = x.y;
        m.v[8] = x.z;
        m.v[12] = -Vector::DotProduct(x, Eye);

        m.v[1] = y.x;
        m.v[5] = y.y;
        m.v[9] = y.z;
        m.v[13] = -Vector::DotProduct(y, Eye);

        m.v[2] = z.x;
        m.v[6] = z.y;
        m.v[10] = z.z;
        m.v[14] = -Vector::DotProduct(z, Eye);

        m.v[15] = 1;
        return m;
    }


    Matrix4x4 Matrix::Perspective(float fovy, float aspect, float near, float far)
    {
        float THalfFov = tan(fovy / 2.0f);
        Matrix4x4 proj = Matrix4x4(0.0f);
        proj.v[0] = 1.0f / (aspect * THalfFov);
        proj.v[5] = 1.0f / THalfFov;
        proj.v[10] = -((far * near) / (far - near));
        proj.v[11] = -1.0f;
        proj.v[14] = -(2.0f * far * near) / (far - near);
        return proj;
    }

    Matrix4x4 Matrix::Orthographic(float left, float right, float bottom, float top)
    {
        float ReciprocalWidth = 1.0f / (right - left);
        float ReciprocalHeight = 1.0f / (top - bottom);
        float fRange = 1.0f / (0.0001f - 1000.0f);

        Matrix4x4 proj = Matrix4x4(0.0f);
        proj.v[0] = ReciprocalWidth * 2;
        proj.v[5] = ReciprocalHeight * 2;
        proj.v[10] = 1.0f;
        proj.v[12] = -(right + left) * ReciprocalWidth;
        proj.v[13] = -(top + bottom) * ReciprocalHeight;
        proj.v[14] = 0.0f;
        proj.v[15] = 1.0f;
        return proj;
    }

    Matrix2x2 Matrix::Mult(Matrix2x2& l, Matrix2x2& r)
    {
        Matrix2x2 mul;
        mul.v[0] = (l.v[0] * r.v[0]) + (l.v[1] * r.v[2]);
        mul.v[1] = (l.v[0] * r.v[1]) + (l.v[1] * r.v[3]);

        mul.v[2] = (l.v[1] * r.v[0]) + (l.v[3] * r.v[2]);
        mul.v[3] = (l.v[1] * r.v[1]) + (l.v[3] * r.v[3]);
        return mul;
    }

    Matrix4x4 Matrix::Scale(Matrix4x4& mat, Vec3 scale)
    {
        mat.v[0] *= scale.x;
        mat.v[1] *= scale.x;
        mat.v[2] *= scale.x;
        mat.v[3] *= scale.x;

        mat.v[4] *= scale.y;
        mat.v[5] *= scale.y;
        mat.v[6] *= scale.y;
        mat.v[7] *= scale.y;

        mat.v[8] *= scale.z;
        mat.v[9] *= scale.z;
        mat.v[10] *= scale.z;
        mat.v[11] *= scale.z;

        return mat;
    }

    Matrix4x4 Matrix::Scale(Vec3 scale)
    {
        return nullptr;
    }

    Matrix4x4 Matrix::Translate(Vec3& vec)
    {
        Matrix4x4 mat;
        mat.v[3] = mat.v[0] * vec.x + mat.v[1] * vec.y + mat.v[2] * vec.z + mat.v[3];
        return mat;
    }
    Matrix4x4 Matrix::Translate(Vec4& vec)
    {
        Matrix4x4 mat;
        mat.v[3] = vec.x;
        mat.v[7] = vec.y;
        mat.v[11] = vec.z;
        mat.v[11] = vec.w;
        return mat;
    }

    Matrix4x4 Matrix::Translate(Matrix4x4& mat, Vec3& vec)
    {
        Vec4 v = Vec4(vec.x, vec.y, vec.z, 1);
        Vec4 top = Vec4(mat.v[0], mat.v[4], mat.v[8], mat.v[12]);
        Vec4 mid = Vec4(mat.v[1], mat.v[5], mat.v[9], mat.v[13]);
        Vec4 deck = Vec4(mat.v[2], mat.v[6], mat.v[10], mat.v[14]);
        Vec4 bot = Vec4(mat.v[3], mat.v[7], mat.v[11], mat.v[15]);
        mat.v[12] += Vector::DotProduct(top, v);
        mat.v[13] += Vector::DotProduct(mid, v);
        mat.v[14] += Vector::DotProduct(deck, v);
        mat.v[15] += Vector::DotProduct(bot, v);

        return mat;
    }

    Matrix4x4 Matrix::Translate(Matrix4x4& mat, Vec4& vec)
    {
        mat.v[3] = vec.x;
        mat.v[7] = vec.y;
        mat.v[11] = vec.z;
        mat.v[11] = vec.w;
        return mat;
    }

    Matrix4x4::Matrix4x4()
    {
        memset(v, 0, sizeof(float) * 16);
        v[0] = 1;
        v[5] = 1;
        v[10] = 1;
        v[15] = 1;
    }

    Matrix4x4::Matrix4x4(float value)
    {
        memset(v, (int)value, sizeof(float) * 16);
    }

    void Matrix4x4::StripTranslation()
    {
        v[3] = 0;
        v[7] = 0;
        v[11] = 0;
        v[12] = 0;
        v[13] = 0;
        v[14] = 0;
        v[15] = 0;
    }


    Matrix4x4::Matrix4x4(float vals[16])
    {
        memcpy(v, vals, sizeof(float) * 16);
    }

    float Matrix4x4::GetValue2D(int row, int col)
    {
        return v[(row * 4) + col];
    }

    void Matrix4x4::Display()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << GetValue2D(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }


    Matrix2x2::Matrix2x2()
    {
        memset(v, 0, sizeof(float) * 4);
        v[0] = 1;
        v[3] = 1;
    }

    Matrix2x2::Matrix2x2(float value)
    {
        memset(v, (int)value, sizeof(float) * 4);
    }

    Matrix2x2::Matrix2x2(float f1, float f2, float f3, float f4)
    {
        v[0] = f1;
        v[1] = f2;
        v[2] = f3;
        v[3] = f4;
    }

    Matrix2x2::Matrix2x2(Matrix2x2& m)
    {
        for (int i = 0; i < 4; i++)
            v[i] = m.v[i];
    }

    Matrix2x2::Matrix2x2(float vals[4])
    {
        memcpy(v, vals, sizeof(float) * 4);
    }

    float Matrix2x2::GetValue2D(int row, int col)
    {
        return v[(row * 2) + col];
    }

    void Matrix2x2::Display()
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                Logger::output(INFO, " %d", GetValue2D(i, j));
            }

        }
    }
}