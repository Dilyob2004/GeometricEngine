#include <Engine/Math/Quaternion.h>

#include <cmath>

namespace MeteorEngine
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
	Quaternion::Quaternion(f32 X, f32 Y, f32 Z, f32 W):
			x(X),
			y(Y),
			z(Z),
			w(W)
	{

	}	
	Quaternion::Quaternion(const Vector3f &eulerAngle)
	{
		Vector3f valueVec = eulerAngle * f32(0.5);


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
		f32 n = 1.f / sqrt(x * x + y * y + z * z + w * w);

		x *= n;
		y *= n;
		z *= n;
		w *= n;
	}
	Quaternion Quaternion::GetNormalized() const
	{
		Quaternion v(*this);
		v.Normalize();
		return v;
	}
}