#ifndef MATRIX3_H
#define MATRIX3_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector3.h>
namespace MeteorEngine
{
	class Matrix4f;
	class METEOR_API Matrix3f
	{
	public:
		Matrix3f();

		Matrix3f(f32 x);

		Matrix3f(const Matrix3f& x);
		Matrix3f(const Matrix4f& x);

		Matrix3f( const Vector3f& column1,
				  const Vector3f& column2,
				  const Vector3f& column3 );

		Matrix3f( f32 m00, f32 m01, f32 m02,
				  f32 m10, f32 m11, f32 m12,
				  f32 m20, f32 m21, f32 m22 );
		~Matrix3f();
		Vector3f& operator[](const s32& i);
		const Vector3f& operator[](s32 i) const;

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


	METEOR_API Matrix3f operator*(const Matrix3f& m1, const f32& x);
	METEOR_API Matrix3f operator*(const f32& x, const Matrix3f& m1);
	METEOR_API Matrix3f operator*(const Matrix3f& m1, const Matrix3f& m2);

}

#endif // MATRIX3_H
