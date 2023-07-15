#include <Engine/Math/Quaternion.h>
#include <cmath>

const FQuaternion FQuaternion::Zero = FQuaternion(0, 0, 0, 0);
const FQuaternion FQuaternion::Identity = FQuaternion();

FQuaternion::FQuaternion() :
	x(0),
	y(0),
	z(0),
	w(1)
{
}
FQuaternion::FQuaternion(F32 X, F32 Y, F32 Z, F32 W):
		x(X),
		y(Y),
		z(Z),
		w(W)
{

}	
FQuaternion::FQuaternion(const Vector3f &eulerAngle)
{
	Vector3f valueVec = eulerAngle * 0.5f;


	Vector3f c = Vector3f(std::cos(valueVec.x), std::cos(valueVec.y), std::cos(valueVec.z));
	Vector3f s = Vector3f(std::sin(valueVec.x), std::sin(valueVec.y), std::sin(valueVec.z));

	x = s.x * c.y * c.z - c.x * s.y * s.z;
	y = c.x * s.y * c.z + s.x * c.y * s.z;
	z = c.x * c.y * s.z - s.x * s.y * c.z;
	w = c.x * c.y * c.z + s.x * s.y * s.z;

}
FQuaternion::~FQuaternion()
{

}

void FQuaternion::Normalize()
{
	F32 n = 1.0f / sqrt(x * x + y * y + z * z + w * w);

	x *= n;
	y *= n;
	z *= n;
	w *= n;
}
FQuaternion FQuaternion::Normalized() const
{
	FQuaternion v(*this);
	v.Normalize();
	return v;
}
FQuaternion& FQuaternion::operator*=(const FQuaternion& r)
{
	const FQuaternion  p(*this);
	const FQuaternion  q(r);

	w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
	x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
	y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
	z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
	return *this;
}

FQuaternion operator*(FQuaternion const& q, FQuaternion const& p)
{
	return FQuaternion(q) *= p;
}
