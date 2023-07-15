#pragma once
#include <Engine/Math/Vector3.h>

class FQuaternion
{
public:
	FQuaternion();
	FQuaternion(F32, F32, F32, F32);
	FQuaternion(const Vector3f& );
	~FQuaternion();

	void Normalize();
	FQuaternion Normalized() const;

	static const FQuaternion Zero;
	static const FQuaternion Identity;

	FQuaternion& operator*=(const FQuaternion& r);

	F32 x, y, z, w;
};
FQuaternion operator*(const FQuaternion& q, const FQuaternion & p);
