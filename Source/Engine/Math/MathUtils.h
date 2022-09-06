#include <Engine/Math/Quaternion.h>

namespace MeteorEngine
{

	METEOR_API bool DecomposeTransform(const Matrix4f& transform, Vector3f& position, Vector3f& rotation, Vector3f& scale);
	METEOR_API Matrix4f Inverse(const Matrix4f& m);

	METEOR_API Matrix4f Ortho(f32 left, f32 right, f32 bottom, f32 top);
	METEOR_API Matrix4f OrthoLH_ZO(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);
	METEOR_API Matrix4f orthoLH_NO(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);
	METEOR_API Matrix4f orthoRH_ZO(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);
	METEOR_API Matrix4f orthoRH_NO(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);
	METEOR_API Matrix4f Perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar);

	METEOR_API Matrix4f Rotate(const Matrix4f& m, f32 angle, const Vector3f& v);

	METEOR_API Matrix4f Rotate(f32 angle, Vector3f const& v);
	METEOR_API Matrix4f TranslateMatrix4(const Matrix4f& m, const Vector3f& v);
	METEOR_API Matrix4f Scale(const Matrix4f& m, const Vector3f& v);

	METEOR_API Vector3f Cross(Vector3f const& x, Vector3f const& y);

	METEOR_API Vector3f operator*(Quaternion const& q, Vector3f const& v);
	METEOR_API Matrix3f toMatrix3(const Quaternion& q);
	METEOR_API Matrix4f toMatrix4(const Quaternion& q);
	METEOR_API Quaternion Rotate(const Quaternion& q, const f32& angle, const Vector3f& v);
	METEOR_API Vector3f Rotate(Quaternion const& q, Vector3f const& v);

	METEOR_API f32 Dot(const Vector3f& v1, const Vector3f& v2);
	METEOR_API Matrix4f LookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);


	METEOR_API f32 Angle(const Vector3f& x, const Vector3f& y);


	METEOR_API Matrix4f Rotate(f32 angle, Vector3f const& v);

	METEOR_API Vector3f Rotate(Vector3f const& v, f32 const& angle, Vector3f const& normal);

}