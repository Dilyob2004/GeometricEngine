#pragma once
#include <Engine/Math/Vector3.h>

class FMatrix4;
class FMatrix3
{
public:
	FMatrix3();

	FMatrix3(F32 x);

	FMatrix3(const FMatrix3& x);
	FMatrix3(const FMatrix4& x);

	FMatrix3( const Vector3f& column1,
				const Vector3f& column2,
				const Vector3f& column3 );

	FMatrix3( F32 m00, F32 m01, F32 m02,
				F32 m10, F32 m11, F32 m12,
				F32 m20, F32 m21, F32 m22 );
	~FMatrix3();
	Vector3f& operator[](const S32& i);
	const Vector3f& operator[](S32 i) const;

	FMatrix3& operator=(FMatrix3 const& m);

	static const FMatrix3 Zero;
	static const FMatrix3 Identity;

private:
	Vector3f Column[3];
};


FMatrix3 operator*(const FMatrix3& m1, const F32& x);
FMatrix3 operator*(const F32& x, const FMatrix3& m1);
FMatrix3 operator*(const FMatrix3& m1, const FMatrix3& m2);

