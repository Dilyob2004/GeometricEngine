#include <Engine/Math/Quaternion.h>

namespace GeometricEngine
{
	#define MATH_PIOVER4                0.785398163397448309616f
	#define MATH_PIX2                   6.28318530717958647693f
	#define MATH_E                      2.71828182845904523536f
	#define MATH_LOG10E                 0.4342944819032518f
	#define MATH_LOG2E                  1.442695040888963387f
	#define MATH_PI                     3.14159265358979323846f
	#define MATH_RADIANS				0.01745329251994329576923690768489f

	#define MIN(a, b) (( (a) < (b) ) ? (a) : (b))
	#define MAX(a, b) (( (a) > (b) ) ? (a) : (b))


	GEOMETRIC_API bool DecomposeTransform(const Matrix4f& transform, Vector3f& position, Vector3f& rotation, Vector3f& scale);
	GEOMETRIC_API Matrix4f Inverse(const Matrix4f& m);

	GEOMETRIC_API Matrix4f Ortho(F32 left, F32 right, F32 bottom, F32 top);
	GEOMETRIC_API Matrix4f Perspective(F32 fovy, F32 aspect, F32 zNear, F32 zFar);
	GEOMETRIC_API Matrix4f Perspective(F32 FOV, F32 Width, F32 Height, F32 zNear, F32 zFar);

	GEOMETRIC_API Matrix4f Rotate(const Matrix4f& m, F32 angle, const Vector3f& v);

	GEOMETRIC_API Matrix4f Rotate(F32 angle, Vector3f const& v);
	GEOMETRIC_API Matrix4f Translate(const Matrix4f& m, const Vector3f& v);
	GEOMETRIC_API Matrix4f Scale(const Matrix4f& m, const Vector3f& v);

	GEOMETRIC_API Vector3f Cross(Vector3f const& x, Vector3f const& y);

	GEOMETRIC_API Vector3f operator*(Quaternion const& q, Vector3f const& v);

	GEOMETRIC_API Matrix3f toMatrix3(const Quaternion& q);
	GEOMETRIC_API Matrix4f toMatrix4(const Quaternion& q);

	GEOMETRIC_API Quaternion Rotate(const Quaternion& q, const F32& angle, const Vector3f& v);
	GEOMETRIC_API Vector3f Rotate(Quaternion const& q, Vector3f const& v);

	GEOMETRIC_API F32 Dot(const Vector3f& v1, const Vector3f& v2);
	GEOMETRIC_API Matrix4f LookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);


	GEOMETRIC_API F32 Angle(const Vector3f& x, const Vector3f& y);


	GEOMETRIC_API Matrix4f Rotate(F32 angle, Vector3f const& v);

	GEOMETRIC_API Vector3f Rotate(Vector3f const& v, F32 const& angle, Vector3f const& normal);



	template<typename T>
	 T* OnPointerValues(const T& Value)
	{
		return &Value[0];
	}
}