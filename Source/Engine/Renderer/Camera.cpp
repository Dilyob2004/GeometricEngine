#include "Camera.h"
#include <Engine/InputCore/InputCore.h>
namespace GeometricEngine
{
	Camera::Camera()
		: View(1.0f)
		, Projection(1.0f)
		, ViewProjection(1.0f)
		, ViewportSize(0.0f, 0.0f)
		, WorldPosition(0.0f, 0.0f, 3.0f)
		, DirectionUp(0.0f, 1.0f, 0.0f)
		, DirectionForward(0.0f, 0.0f, -1.0f)
		, FOV(0), DepthFar(0), DepthNear(0)
	{
	}
	Camera::Camera(F32 Fov, F32 zNear, F32 zFar)
		: View(1.0f)
		, Projection(1.0f)
		, ViewProjection(1.0f)
		, ViewportSize(0.0f, 0.0f)
		, WorldPosition(0.0f, 0.0f, -10.0f)
		, DirectionUp(0.0f, 1.0f, 0.0f)
		, DirectionForward(0.0f, 0.0f, -1.0f)
		, FOV(Fov)
		, DepthNear(zNear)
		, DepthFar(zFar)
	{
		RecalculateViewProjection();
	}
	void Camera::RecalculateViewProjection()
	{
		View = LookAt(WorldPosition, WorldPosition + DirectionForward, DirectionUp);
		Projection = Perspective(FOV, ViewportSize.x / ViewportSize.y, DepthNear, DepthFar);
		ViewProjection =  Projection * View;
	}
	void Camera::OnTick(F32 TimeStep)
	{
		if (Input::GetKey(KeyCode::W)) WorldPosition += 0.1f * DirectionForward;
		if (Input::GetKey(KeyCode::S)) WorldPosition -= 0.1f * DirectionForward;

		if (Input::GetKey(KeyCode::A)) WorldPosition -= 0.1f * Cross(DirectionForward, DirectionUp).GetNormalized();
		if (Input::GetKey(KeyCode::D)) WorldPosition += 0.1f * Cross(DirectionForward, DirectionUp).GetNormalized();
		

		if (Input::GetKey(KeyCode::Q)) WorldPosition += 0.1f * DirectionUp;
		if (Input::GetKey(KeyCode::E)) WorldPosition -= 0.1f * DirectionUp;


		if (Input::GetKey(KeyCode::Up)) DirectionForward = Rotate(DirectionForward, -1, Cross(DirectionForward, DirectionUp).GetNormalized());
		if (Input::GetKey(KeyCode::Down)) DirectionForward = Rotate(DirectionForward, 1, Cross(DirectionForward, DirectionUp).GetNormalized());



		if (Input::GetKey(KeyCode::Left)) DirectionForward = Rotate(DirectionForward, -1, DirectionUp);
		if (Input::GetKey(KeyCode::Right)) DirectionForward = Rotate(DirectionForward, 1, DirectionUp);
		RecalculateViewProjection();
	}
}