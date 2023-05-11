#include <Engine/Math/Quaternion.h>
#include <cmath>

namespace GeometricEngine
{
	const Quaternion Quaternion::Zero = Quaternion(0, 0, 0, 0);
	const Quaternion Quaternion::Identity = Quaternion();

	Quaternion::Quaternion() :
		x(0),
		y(0),
		z(0),
		w(1)
	{
	}
	Quaternion::Quaternion(F32 X, F32 Y, F32 Z, F32 W):
			x(X),
			y(Y),
			z(Z),
			w(W)
	{

	}	
	Quaternion::Quaternion(const Vector3f &eulerAngle)
	{
		Vector3f valueVec = eulerAngle * 0.5f;


		Vector3f c = Vector3f(std::cos(valueVec.x), std::cos(valueVec.y), std::cos(valueVec.z));
		Vector3f s = Vector3f(std::sin(valueVec.x), std::sin(valueVec.y), std::sin(valueVec.z));

		x = s.x * c.y * c.z - c.x * s.y * s.z;
		y = c.x * s.y * c.z + s.x * c.y * s.z;
		z = c.x * c.y * s.z - s.x * s.y * c.z;
		w = c.x * c.y * c.z + s.x * s.y * s.z;

	}
	Quaternion::~Quaternion()
	{

	}

	void Quaternion::Normalize()
	{
		F32 n = 1.0f / sqrt(x * x + y * y + z * z + w * w);

		x *= n;
		y *= n;
		z *= n;
		w *= n;
	}
	Quaternion Quaternion::Normalized() const
	{
		Quaternion v(*this);
		v.Normalize();
		return v;
	}
	Quaternion& Quaternion::operator*=(const Quaternion& r)
	{
		const Quaternion  p(*this);
		const Quaternion  q(r);

		w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return *this;
	}

}