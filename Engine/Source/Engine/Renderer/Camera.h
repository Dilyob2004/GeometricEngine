#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Math/Vector2.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/MathUtils.h>

class Camera
{
public:
	Camera() = default;
	FMatrix4 GetView() const { return View; }
	FMatrix4 GetProjection() const { return Projection; }
	FMatrix4 GetViewProjection() const { return Projection * View; }


	void SetView(const FMatrix4& Matrix) { View = Matrix; }
	void SetProjection(const FMatrix4& Matrix) { Projection = Matrix; }
protected:

	FMatrix4	View { 1.0f };
	FMatrix4	Projection { 1.0f };
};
class EditorCamera : public Camera
{
public:
	EditorCamera();
	EditorCamera(const Vector2f& );
	void OnTick(F32 TimeStep);
	void OnResize(const Vector2f& Size);

	Vector2f GetPosition() const { return Vector2f(Position.x, Position.y); }
	Vector3f ScreenToWorldSpace(const Vector2f& MousePosition);
private:
	void Invalidate();

	Vector2f	ViewportSize;
	Vector3f	Position;
	Vector3f	LastPosition;
	F32			Rotation;
	F32			AspectRatio;
	F32			ZoomLevel;
	F32			Speed;

};
class FLevelCamera : public Camera
{
public:
	FLevelCamera();
	FLevelCamera(const Vector2f&);
	void OnTick(F32 TimeStep);
	void OnResize(const Vector2f& Size);

	Vector2f GetPosition() const { return Vector2f(Position.x, Position.y); }
	Vector3f ScreenToWorldSpace(const Vector2f& MousePosition);
private:
	void Invalidate();

	Vector2f	ViewportSize;
	Vector3f	Position;
	Vector3f	LastPosition;
	F32			Rotation;
	F32			AspectRatio;
	F32			ZoomLevel;
	F32			Speed;

};
class CameraPerspective : public Camera
{
public:
	CameraPerspective() = default;
	CameraPerspective(F32 fovy, F32 aspect, F32 zNear, F32 zFar);

	void OnTick(F32 TimeStep);
	void OnResize(const Vector2f& Size) { m_aspectRatio = Size.x / Size.y; Invalidate(); }
private:
	void Invalidate();


	Vector3f	m_position{ 0, 0, 10 };
	Vector3f	m_up{ 0, 1, 0 };
	Vector3f	m_forward{ 0, 0, -1 };
	F32			m_aspectRatio, m_fov, m_zNear, m_zFar;
};
/*class GEOMETRIC_API Camera
{
public:
	Camera();
	Camera(F32 Fov, F32 zNear = 0.01f, F32 zFar = 1000.f);

	FMatrix4 GetView() const { return View; }
	FMatrix4 GetWorld() const { return World; }
	FMatrix4 GetProjection() const { return Projection; }
	FMatrix4 GetViewProjection() const { return ViewProjection; }

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

	FMatrix4	View;
	FMatrix4	World;
	FMatrix4	Projection;
	FMatrix4	ViewProjection;

	Vector2f	ViewportSize;
	Vector3f	WorldPosition;
	Vector3f	DirectionUp;
	Vector3f	DirectionForward;


	F32 FOV;
	F32 DepthNear;
	F32 DepthFar;
};*/

#endif // !CAMERA_H
