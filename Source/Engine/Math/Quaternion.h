#ifndef QUATERNION_H
#define QUATERNION_H
#include <Engine/Math/Matrix4.h>

namespace MeteorEngine
{
	class METEOR_API Quaternion
	{
	public:
		Quaternion();
		Quaternion(f32, f32, f32, f32);
		Quaternion(const Vector3f& );
		~Quaternion();

		void Normalize();
		Quaternion GetNormalized() const;
		static const Quaternion Zero;
		static const Quaternion Identity;

		Quaternion& operator*=(const Quaternion& r)
		{
			const Quaternion  p(*this);
			const Quaternion  q(r);

			w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
			x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
			y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
			z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
			return *this;
		}

		f32 x, y, z, w;
	};
	METEOR_API Quaternion operator*(Quaternion const& q, Quaternion const& p);

}
#endif // !QUATERNION_H
