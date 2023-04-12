#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Math/Vector2.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/MathUtils.h>
namespace GeometricEngine
{
	class GEOMETRIC_API Camera
	{
	public:
		Camera();
		Camera(F32 Fov, F32 zNear = 0.01f, F32 zFar = 1000.f);

		Matrix4f GetView() const { return View; }
		Matrix4f GetProjection() const { return Projection; }
		Matrix4f GetViewProjection() const { return ViewProjection; }

		void SetProjection(F32 Fov, F32 zNear, F32 zFar)
		{
			FOV = Fov;
			DepthNear = zNear;
			DepthFar = zFar;
			RecalculateViewProjection();
		}
		void OnTick(F32 TimeStep);
		void OnResize(const Vector2f& Size) { ViewportSize = Size; }
	private:


		void RecalculateViewProjection();

		Matrix4f	View;
		Matrix4f	Projection;
		Matrix4f	ViewProjection;

		Vector2f	ViewportSize;
		Vector3f	WorldPosition;
		Vector3f	DirectionUp;
		Vector3f	DirectionForward;


		F32 FOV;
		F32 DepthNear;
		F32 DepthFar;
	};
}
#endif // !CAMERA_H
