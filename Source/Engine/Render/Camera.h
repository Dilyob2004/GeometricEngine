#ifndef CAMERA_H
#define CAMERA_H
#include <Engine/Math/Vector2.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Core/Event.h>
#include <Engine/Math/Quaternion.h>
namespace MeteorEngine
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(f32 fovy, f32 aspect, f32 zNear, f32 zFar);

		const Matrix4f& GetProjection() const { return m_projectionMatrix; }
		const Matrix4f& GetView() const { return m_viewMatrix; }
		const Matrix4f& GetViewProjection() const { return m_viewProjectionMatrix; }
		void OnUpdate(f32 ftime);
		void OnResize(const Vector2u& size) { m_aspectRatio = (f32)size.x / (f32)size.y;  RecalculateVewMatrix(); }
		void OnEvent(Event& event);
	private:
		void RecalculateVewMatrix();
		Matrix4f	m_viewProjectionMatrix;
		Matrix4f	m_projectionMatrix;

		
		Vector2u	m_viewPortSize{1280, 720};
		Matrix4f	m_viewMatrix;
		Vector3f	m_position{ 0, 0, 10 };
		Vector3f	m_up{ 0, 1, 0 };
		Vector3f	m_forward{ 0, 0, -1 };
		f32			m_aspectRatio, m_fov, m_zNear, m_zFar;
	};
	/**class Camera
	{
	public:
		Camera() = default;
		Camera(f32 fovy, f32 aspect, f32 zNear, f32 zFar);
		


		const Vector3f& GetPosition() const { return m_position; }
		void SetPosition(const Vector3f& position) { m_position = position; UpdateView(); }

		float GetDistance() const { return m_distance; }
		void SetDistance(float distance) { m_distance = distance; }

		const Matrix4f& GetProjection() const { return m_projectionMatrix; }
		const Matrix4f& GetView() const { return m_viewMatrix; }
		const Matrix4f& GetViewProjection() const { return m_viewProjectionMatrix; }


		void OnUpdate(f32 ftime);
		void OnResize(const Vector2u& size) { m_viewPortSize = size;  UpdateProjection();  }
		void OnEvent(Event& event);

		Vector3f	GetUpDirection() const;
		Vector3f	GetRightDirection() const;
		Vector3f	GetForwardDirection() const;
		Vector3f	CalculatePosition() const;
		Quaternion	GetOrientation() const;

		float GetPitch() const { return m_pitch; }
		float GetYaw() const { return m_yaw; }
		float RotationSpeed() const { return 1; }

		float ZoomSpeed() const;
	private:
		void MousePan(const Vector2f& delta);

		void MouseRotate(const Vector2f& delta);

		void MouseZoom(f32 delta);
		Vector2f PanSpeed() const;
		void UpdateView();
		void UpdateProjection();
	private:
		Matrix4f	m_viewProjectionMatrix;
		Matrix4f	m_projectionMatrix;
		Matrix4f	m_viewMatrix;
		Vector3f	m_position{0, 0, 0};
		Vector3f	m_focalPoint{0, 0, 0};
		Vector2f	m_initialMousePosition {0, 0};
		f32			m_distance = 10, m_fov = 0, m_zNear = 0.1f, m_zFar = 1000.f;
		f32			m_pitch = 0, m_yaw = 0, m_aspectRatio = 1.778f;
		Vector2u	m_viewPortSize{1280, 720};
	};*/
}
#endif


