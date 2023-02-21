#ifndef MATRIX4_H
#define MATRIX4_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector4.h>
#include <Engine/Math/Matrix3.h>
namespace GeometricEngine
{
    class METEOR_API Matrix4f
    {
    public:
        Matrix4f();

        Matrix4f(F32 x);

        Matrix4f(const Matrix4f& x);
        Matrix4f(const Matrix3f& x);

        Matrix4f(const Vector4f &column1,
                 const Vector4f &column2,
                 const Vector4f &column3,
                 const Vector4f &column4);

        Matrix4f(F32 m00, F32 m01, F32 m02, F32 m03,
                 F32 m10, F32 m11, F32 m12, F32 m13,
                 F32 m20, F32 m21, F32 m22, F32 m23,

                 F32 m30, F32 m31, F32 m32, F32 m33);
        ~Matrix4f();
        Vector4f& operator[](const S32& i);
        const Vector4f& operator[](S32 i) const;

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


	METEOR_API Matrix4f operator*(const Matrix4f& m1, const F32 &x);
	METEOR_API Matrix4f operator*(const F32 &x, const Matrix4f& m1);
	METEOR_API Matrix4f operator*(const Matrix4f& m1, const Matrix4f &m2);


}

#endif // MATRIX4_H
