#include <Engine/Math/Matrix3.h>
#include <Engine/Math/Matrix4.h>
namespace GeometricEngine
{

	const Matrix3f Matrix3f::Identity = Matrix3f(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	const Matrix3f Matrix3f::Zero = Matrix3f(
		0, 0, 0,
		0, 0, 0,
		0, 0, 0);


	Matrix3f::Matrix3f()
	{
		*this = Matrix3f::Identity;
	}
	Matrix3f::Matrix3f(F32 x)
	{
		Column[0] = Vector3f(x, 0, 0);
		Column[1] = Vector3f(0, x, 0);
		Column[2] = Vector3f(0, 0, x);
	}
	Matrix3f::Matrix3f(const Matrix3f& x)
	{
		Column[0] = x[0];
		Column[1] = x[1];
		Column[2] = x[2];
	}	
	Matrix3f::Matrix3f(const Matrix4f& x)
	{
		Column[0] = Vector3f (x[0].x, x[0].y, x[0].z);
		Column[1] = Vector3f (x[1].x, x[1].y, x[1].z);
		Column[2] = Vector3f (x[2].x, x[2].y, x[2].z);
	}

	Matrix3f::Matrix3f(const Vector3f& column1,
		const Vector3f& column2,
		const Vector3f& column3)
	{
		Column[0] = column1;
		Column[1] = column2;
		Column[2] = column3;
	}
	Matrix3f::Matrix3f( F32 m00, F32 m01, F32 m02,
						F32 m10, F32 m11, F32 m12,
					    F32 m20, F32 m21, F32 m22)
	{
		Column[0] = Vector3f(m00, m01, m02);
		Column[1] = Vector3f(m10, m11, m12);
		Column[2] = Vector3f(m20, m21, m22);
	}
	Matrix3f::~Matrix3f()
	{
	}
	Vector3f& Matrix3f::operator[](const S32& i)
	{
		return Column[i];
	}

	const Vector3f& Matrix3f::operator[](S32 i) const
	{
		return Column[i];
	}

	Matrix3f& Matrix3f::operator=(Matrix3f const& m)
	{
		Column[0] = m[0];
		Column[1] = m[1];
		Column[2] = m[2];
		return *this;
	}

	Matrix3f operator*(const Matrix3f& m1, const F32& x)
	{
		return Matrix3f(m1[0] * x,
						m1[1] * x,
						m1[2] * x);
	}
	Matrix3f operator*(const F32& x, const Matrix3f& m1)
	{
		return Matrix3f(m1[0] * x,
						m1[1] * x,
						m1[2] * x);
	}
	Matrix3f operator*(const Matrix3f& m1, const Matrix3f& m2)
	{
		const Vector3f SrcA0 = m1[0];
		const Vector3f SrcA1 = m1[1];
		const Vector3f SrcA2 = m1[2];

		const Vector3f SrcB0 = m2[0];
		const Vector3f SrcB1 = m2[1];
		const Vector3f SrcB2 = m2[2];

		return Matrix3f(SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2],
						SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2],
						SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2]);
	}
}
