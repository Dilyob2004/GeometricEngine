#include "Camera.h"
#include <Engine/InputCore/InputCore.h>

CameraPerspective::CameraPerspective(F32 fovy, F32 aspect, F32 zNear, F32 zFar) :
	m_fov(fovy),
	m_aspectRatio(aspect),
	m_zNear(zNear),
	m_zFar(zFar)
{
	Invalidate();
}
void CameraPerspective::Invalidate()
{
	View = MathUtils::LookAt(m_position, m_position + m_forward, m_up);
	Projection = MathUtils::Perspective(m_fov * MATH_RADIANS, m_aspectRatio, m_zNear, m_zFar);
}

void CameraPerspective::OnTick(F32 ftime)
{
	if (Input::GetKey(KeyCode::W)) m_position += 0.1f * m_forward;
	if (Input::GetKey(KeyCode::S)) m_position -= 0.1f * m_forward;


	if (Input::GetKey(KeyCode::D)) m_position -= 0.1f * MathUtils::Cross(m_forward, m_up).GetNormalized();
	if (Input::GetKey(KeyCode::A)) m_position += 0.1f * MathUtils::Cross(m_forward, m_up).GetNormalized();


	if (Input::GetKey(KeyCode::Q)) m_position += 0.1f * m_up;
	if (Input::GetKey(KeyCode::E)) m_position -= 0.1f * m_up;


	if (Input::GetKey(KeyCode::Up)) m_forward = MathUtils::Rotate(m_forward, -1, MathUtils::Cross(m_forward, m_up).GetNormalized());
	if (Input::GetKey(KeyCode::Down)) m_forward = MathUtils::Rotate(m_forward, 1, MathUtils::Cross(m_forward, m_up).GetNormalized());



	if (Input::GetKey(KeyCode::Left)) m_forward = MathUtils::Rotate(m_forward, 1, m_up);
	if (Input::GetKey(KeyCode::Right)) m_forward = MathUtils::Rotate(m_forward, -1, m_up);


	Invalidate();
}

EditorCamera::EditorCamera()
	: AspectRatio(0.0f)
	, Speed(1.0f)
	, Position(0.0f, 0.0f, 0.0f)
	, LastPosition(Position)
	, Rotation(0.0f)
	, ZoomLevel(1.0f)
	, ViewportSize(0.0f, 0.0f)
{
}

EditorCamera::EditorCamera(const Vector2f& ViewSize)
	: AspectRatio(0.0f)
	, Speed(1.0f)
	, Position(0.0f, 0.0f, 0.0f)
	, LastPosition(Position)
	, Rotation(0.0f)
	, ZoomLevel(1.0f)
	, ViewportSize(0.0f, 0.0f)
{
	OnResize(ViewSize);
}

void EditorCamera::OnResize(const Vector2f& Size)
{
	ViewportSize = Size;
	AspectRatio = Size.x / Size.y;
	Invalidate();
}
Vector3f EditorCamera::ScreenToWorldSpace(const Vector2f& MousePosition)
{
	F32 X = 2.0f * MousePosition.x / ViewportSize.x - 1.0f;
	F32 Y = 2.0f * MousePosition.y / ViewportSize.y - 1.0f;

	Vector3f ScreenPosition = Vector3f(X, -Y, -1.0f);

	return MathUtils::Inverse(Projection * View) * ScreenPosition;
}
void EditorCamera::OnTick(F32 TimeStep)
{
	if (Input::GetMouseButtonDown(MouseCode::ButtonRight)) 
		LastPosition = -ScreenToWorldSpace(Input::GetMousePosition());
		
	if (Input::GetMouseButton(MouseCode::ButtonRight))
	{
		Vector3f NewPosition = -ScreenToWorldSpace(Input::GetMousePosition());
		Vector3f Offset = NewPosition - LastPosition;

		LastPosition = NewPosition;

		Position += Offset;
	}

	if (Input::GetMouseWhellDelta() != 0)
	{
		ZoomLevel -= Input::GetMouseWhellDelta() / 2.f;
		ZoomLevel = MAX(ZoomLevel, 0.3f);
	}
	Invalidate();
}

void EditorCamera::Invalidate()
{
	View = MathUtils::Inverse(MathUtils::Translate(FMatrix4::Identity, Position) 
		* MathUtils::Rotate(FMatrix4::Identity, Rotation, Vector3f(0, 0, 1)));

	Projection = MathUtils::Ortho(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);


}


FLevelCamera::FLevelCamera()
	: AspectRatio(0.0f)
	, Speed(1.0f)
	, Position(0.0f, 0.0f, 0.0f)
	, LastPosition(Position)
	, Rotation(0.0f)
	, ZoomLevel(1.0f)
	, ViewportSize(0.0f, 0.0f)
{
}

FLevelCamera::FLevelCamera(const Vector2f& ViewSize)
	: AspectRatio(0.0f)
	, Speed(1.0f)
	, Position(0.0f, 0.0f, 0.0f)
	, LastPosition(Position)
	, Rotation(0.0f)
	, ZoomLevel(1.0f)
	, ViewportSize(0.0f, 0.0f)
{
	OnResize(ViewSize);
}

void FLevelCamera::OnResize(const Vector2f& Size)
{
	ViewportSize = Size;
	AspectRatio = Size.x / Size.y;
	Invalidate();
}
Vector3f FLevelCamera::ScreenToWorldSpace(const Vector2f& MousePosition)
{
	F32 X = 2.0f * MousePosition.x / ViewportSize.x - 1.0f;
	F32 Y = 2.0f * MousePosition.y / ViewportSize.y - 1.0f;

	Vector3f ScreenPosition = Vector3f(X, -Y, -1.0f);

	return MathUtils::Inverse(Projection * View) * ScreenPosition;
}
void FLevelCamera::OnTick(F32 TimeStep)
{
	if (Input::GetMouseButtonDown(MouseCode::ButtonRight))
		LastPosition = -ScreenToWorldSpace(Input::GetMousePosition());

	if (Input::GetMouseButton(MouseCode::ButtonRight))
	{
		Vector3f NewPosition = -ScreenToWorldSpace(Input::GetMousePosition());
		Vector3f Offset = NewPosition - LastPosition;

		LastPosition = NewPosition;

		Position += Offset;
	}

	if (Input::GetMouseWhellDelta() != 0)
	{
		ZoomLevel -= Input::GetMouseWhellDelta() / 2.f;
		ZoomLevel = MAX(ZoomLevel, 0.3f);
	}
	Invalidate();
}

void FLevelCamera::Invalidate()
{
	View = MathUtils::Inverse(MathUtils::Translate(FMatrix4::Identity, Position)
		* MathUtils::Rotate(FMatrix4::Identity, Rotation, Vector3f(0, 0, 1)));

	Projection = MathUtils::Ortho(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
}
/*
Camera::Camera()
	: View(1.0f)
	, Projection(1.0f)
	, ViewProjection(1.0f)
	, ViewportSize(0.0f, 0.0f)
	, WorldPosition(0.0f, 0.0f, 5.0f)
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
	World = Translate(FMatrix4::Identity, WorldPosition) * Rotate(FMatrix4::Identity, 30, DirectionForward);
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
*/