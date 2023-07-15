#include <Engine/Math/Matrix3.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Quaternion.h>

#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_RADIANS				0.01745329251994329576923690768489f	

#define MIN(a, b) (( (a) < (b) ) ? (a) : (b))
#define MAX(a, b) (( (a) > (b) ) ? (a) : (b))


namespace MathUtils
{



		bool DecomposeTransform(const FMatrix4& transform, Vector3f& position, Vector3f& rotation, Vector3f& scale);
		FMatrix4 Inverse(const FMatrix4& m);

		FMatrix4 Ortho(F32 left, F32 right, F32 bottom, F32 top);
		FMatrix4 Perspective(F32 fovy, F32 aspect, F32 zNear, F32 zFar);
		FMatrix4 Perspective(F32 FOV, F32 Width, F32 Height, F32 zNear, F32 zFar);

		FMatrix4 Rotate(const FMatrix4& m, F32 angle, const Vector3f& v);

		FMatrix4 Rotate(F32 angle, Vector3f const& v);
		FMatrix4 Translate(const FMatrix4& m, const Vector3f& v);
		FMatrix4 Scale(const FMatrix4& m, const Vector3f& v);

		Vector3f Cross(Vector3f const& x, Vector3f const& y);

		Vector3f operator*(FQuaternion const& q, Vector3f const& v);

		FMatrix3 QuaternionToMatrix3(const FQuaternion& q);
		FMatrix4 QuaternionToMatrix4(const FQuaternion& q);

		FQuaternion Rotate(const FQuaternion& q, const F32& angle, const Vector3f& v);
		Vector3f Rotate(FQuaternion const& q, Vector3f const& v);

		F32 Dot(const Vector3f& v1, const Vector3f& v2);
		FMatrix4 LookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);


		F32 Angle(const Vector3f& x, const Vector3f& y);


		FMatrix4 Rotate(F32 angle, Vector3f const& v);

		Vector3f Rotate(Vector3f const& v, F32 const& angle, Vector3f const& normal);

}
