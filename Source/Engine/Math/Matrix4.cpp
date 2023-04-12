#include <Engine/Math/Matrix4.h>
namespace GeometricEngine
{

    const Matrix4f Matrix4f::Identity = Matrix4f(
                        1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);

    const Matrix4f Matrix4f::Zero = Matrix4f(
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0 );


    Matrix4f::Matrix4f()
    {
        *this = Matrix4f::Identity;
    }
    Matrix4f::Matrix4f(F32 x)
    {
        Column[0] = Vector4f(x, 0, 0, 0);
        Column[1] = Vector4f(0, x, 0, 0);
        Column[2] = Vector4f(0, 0, x, 0);
        Column[3] = Vector4f(0, 0, 0, x);
    }
    Matrix4f::Matrix4f(const Matrix4f& x)
    {
        Column[0] = x[0];
        Column[1] = x[1];
        Column[2] = x[2];
        Column[3] = x[3];
    }
	Matrix4f::Matrix4f(const Matrix3f& x)
	{
		Column[0] = Vector4f(x[0][0], x[0][1], x[0][2], 0);
		Column[1] = Vector4f(x[1][0], x[1][1], x[1][2], 0);
		Column[2] = Vector4f(x[2][0], x[2][1], x[2][2], 0);
		Column[3] = Vector4f(0,       0,       0,       1);
	}
    Matrix4f::Matrix4f( const Vector4f &column1,
                        const Vector4f &column2,
                        const Vector4f &column3,
                        const Vector4f &column4 )
    {
        Column[0] = column1;
        Column[1] = column2;
        Column[2] = column3;
        Column[3] = column4;
    }
    Matrix4f::Matrix4f( F32 m00, F32 m01, F32 m02, F32 m03,
                        F32 m10, F32 m11, F32 m12, F32 m13,
                        F32 m20, F32 m21, F32 m22, F32 m23,
                        F32 m30, F32 m31, F32 m32, F32 m33 )
    {
        Column[0] = Vector4f(m00, m01, m02, m03);
        Column[1] = Vector4f(m10, m11, m12, m13);
        Column[2] = Vector4f(m20, m21, m22, m23);
        Column[3] = Vector4f(m30, m31, m32, m33);
    }
    Matrix4f::~Matrix4f()
    {
    }
    Vector4f& Matrix4f::operator[](const S32& i)
    {
        return Column[i];
    }

    const Vector4f& Matrix4f::operator[](S32 i) const
    {
        return Column[i];
    }

	Matrix4f& Matrix4f::operator=(const Matrix4f & m)
	{
		Column[0] = m[0];
		Column[1] = m[1];
		Column[2] = m[2];
		Column[3] = m[3];
		return *this;
	}

    Matrix4f operator*(const Matrix4f& m1, const F32 &x)
    {
        return Matrix4f(m1[0] * x,
                        m1[1] * x,
                        m1[2] * x,
                        m1[3] * x);
    }
    Matrix4f operator*(const F32 &x, const Matrix4f& m1)
    {
        return Matrix4f(m1[0] * x,
                        m1[1] * x,
                        m1[2] * x,
                        m1[3] * x);
    }
    Matrix4f operator*(const Matrix4f& m1, const Matrix4f &m2)
    {
        Vector4f const SrcA0 = m1[0];
        Vector4f const SrcA1 = m1[1];
        Vector4f const SrcA2 = m1[2];
        Vector4f const SrcA3 = m1[3];

        Vector4f const SrcB0 = m2[0];
        Vector4f const SrcB1 = m2[1];
        Vector4f const SrcB2 = m2[2];
        Vector4f const SrcB3 = m2[3];

        return Matrix4f(SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3],
                        SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3],
                        SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3],
                        SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3]);
    }

}
