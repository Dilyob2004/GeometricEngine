#ifndef MATRIX3_H
#define MATRIX3_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector3.h>
namespace GeometricEngine
{
	class Matrix4f;
	class METEOR_API Matrix3f
	{
	public:
		Matrix3f();

		Matrix3f(F32 x);

		Matrix3f(const Matrix3f& x);
		Matrix3f(const Matrix4f& x);

		Matrix3f( const Vector3f& column1,
				  const Vector3f& column2,
				  const Vector3f& column3 );

		Matrix3f( F32 m00, F32 m01, F32 m02,
				  F32 m10, F32 m11, F32 m12,
				  F32 m20, F32 m21, F32 m22 );
		~Matrix3f();
		Vector3f& operator[](const S32& i);
		const Vector3f& operator[](S32 i) const;

		Matrix3f& operator=(Matrix3f const& m)
		{
			m_column[0] = m[0];
			m_column[1] = m[1];
			m_column[2] = m[2];
			return *this;
		}

		static const Matrix3f Zero;
		static const Matrix3f Identity;

	private:
		Vector3f m_column[3];
	};


	METEOR_API Matrix3f operator*(const Matrix3f& m1, const F32& x);
	METEOR_API Matrix3f operator*(const F32& x, const Matrix3f& m1);
	METEOR_API Matrix3f operator*(const Matrix3f& m1, const Matrix3f& m2);

}

#endif // MATRIX3_H
