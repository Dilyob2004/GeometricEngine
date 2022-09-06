#include <Engine/Math/Matrix4.h>
namespace MeteorEngine
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
    Matrix4f::Matrix4f(f32 x)
    {
        m_column[0] = Vector4f(x, 0, 0, 0);
        m_column[1] = Vector4f(0, x, 0, 0);
        m_column[2] = Vector4f(0, 0, x, 0);
        m_column[3] = Vector4f(0, 0, 0, x);
    }
    Matrix4f::Matrix4f(const Matrix4f& x)
    {
        m_column[0] = x[0];
        m_column[1] = x[1];
        m_column[2] = x[2];
        m_column[3] = x[3];
    }
	Matrix4f::Matrix4f(const Matrix3f& x)
	{
		m_column[0] = Vector4f(x[0][0], x[0][1], x[0][2], 0);
		m_column[1] = Vector4f(x[1][0], x[1][1], x[1][2], 0);
		m_column[2] = Vector4f(x[2][0], x[2][1], x[2][2], 0);
		m_column[3] = Vector4f(0, 0, 0, 1);
	}
    Matrix4f::Matrix4f( const Vector4f &column1,
                        const Vector4f &column2,
                        const Vector4f &column3,
                        const Vector4f &column4 )
    {
        m_column[0] = column1;
        m_column[1] = column2;
        m_column[2] = column3;
        m_column[3] = column4;
    }
    Matrix4f::Matrix4f( f32 m00, f32 m01, f32 m02, f32 m03,
                        f32 m10, f32 m11, f32 m12, f32 m13,
                        f32 m20, f32 m21, f32 m22, f32 m23,
                        f32 m30, f32 m31, f32 m32, f32 m33 )
    {
        /**
        m_column[0] = Vector4f(m00, m10, m20, m30);
        m_column[1] = Vector4f(m01, m11, m21, m31);
        m_column[2] = Vector4f(m02, m12, m22, m32);
        m_column[3] = Vector4f(m03, m13, m23, m33);

        */
        m_column[0] = Vector4f(m00, m01, m02, m03);
        m_column[1] = Vector4f(m10, m11, m12, m13);
        m_column[2] = Vector4f(m20, m21, m22, m23);
        m_column[3] = Vector4f(m30, m31, m32, m33);
    }
    Matrix4f::~Matrix4f()
    {
    }
    Vector4f& Matrix4f::operator[](const s32& i)
    {
        return m_column[i];
    }

    const Vector4f& Matrix4f::operator[](s32 i) const
    {
        return m_column[i];
    }

    Matrix4f operator*(const Matrix4f& m1, const f32 &x)
    {
        return Matrix4f(m1[0] * x,
                        m1[1] * x,
                        m1[2] * x,
                        m1[3] * x);
    }
    Matrix4f operator*(const f32 &x, const Matrix4f& m1)
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
