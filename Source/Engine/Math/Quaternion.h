#ifndef QUATERNION_H
#define QUATERNION_H
#include <Engine/Math/Matrix4.h>

namespace GeometricEngine
{
	class GEOMETRIC_API Quaternion
	{
	public:
		Quaternion();
		Quaternion(F32, F32, F32, F32);
		Quaternion(const Vector3f& );
		~Quaternion();

		void Normalize();
		Quaternion Normalized() const;
		static const Quaternion Zero;
		static const Quaternion Identity;

		Quaternion& operator*=(const Quaternion& r);

		F32 x, y, z, w;
	};
	GEOMETRIC_API Quaternion operator*(Quaternion const& q, Quaternion const& p);

}
#endif // !QUATERNION_H
