#ifndef MATRIX4_H
#define MATRIX4_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector4.h>
#include <Engine/Math/Matrix3.h>
namespace MeteorEngine
{
    class METEOR_API Matrix4f
    {
    public:
        Matrix4f();

        Matrix4f(f32 x);

        Matrix4f(const Matrix4f& x);
        Matrix4f(const Matrix3f& x);

        Matrix4f(const Vector4f &column1,
                 const Vector4f &column2,
                 const Vector4f &column3,
                 const Vector4f &column4);

        Matrix4f(f32 m00, f32 m01, f32 m02, f32 m03,
                 f32 m10, f32 m11, f32 m12, f32 m13,
                 f32 m20, f32 m21, f32 m22, f32 m23,

                 f32 m30, f32 m31, f32 m32, f32 m33);
        ~Matrix4f();
        Vector4f& operator[](const s32& i);
        const Vector4f& operator[](s32 i) const;

        Matrix4f& operator=(Matrix4f const& m)
        {
            m_column[0] = m[0];
            m_column[1] = m[1];
            m_column[2] = m[2];
            m_column[3] = m[3];
            return *this;
        }

        static const Matrix4f Zero;
        static const Matrix4f Identity;

    private:
        Vector4f m_column[4];
    };


	METEOR_API Matrix4f operator*(const Matrix4f& m1, const f32 &x);
	METEOR_API Matrix4f operator*(const f32 &x, const Matrix4f& m1);
	METEOR_API Matrix4f operator*(const Matrix4f& m1, const Matrix4f &m2);


}

#endif // MATRIX4_H
