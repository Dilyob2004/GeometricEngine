#include <Engine/Render/Camera.h>
#include <Engine/Core/Input.h>
#include <Engine/Math/MathUtils.h>
#include <Engine/Core/Application.h>
namespace MeteorEngine
{
	Camera::Camera(f32 fovy, f32 aspect, f32 zNear, f32 zFar) :
		m_fov(fovy),
		m_aspectRatio(aspect),
		m_zNear(zNear),
		m_zFar(zFar)
	{
		RecalculateVewMatrix();
	}
	void Camera::RecalculateVewMatrix()
	{
		m_viewMatrix = LookAt(m_position, m_position + m_forward, m_up);
		m_projectionMatrix = Perspective(m_fov * MATH_RADIANS, m_aspectRatio, m_zNear, m_zFar);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void Camera::OnUpdate(f32 ftime)
	{
		if (Input::GetKeyDown(KeyCode::W)) m_position += 0.1f * m_forward;
		if (Input::GetKeyDown(KeyCode::S)) m_position -= 0.1f * m_forward;


		if (Input::GetKeyDown(KeyCode::D)) m_position -= 0.1f * Cross(m_forward, m_up).GetNormalized();
		if (Input::GetKeyDown(KeyCode::A)) m_position += 0.1f * Cross(m_forward, m_up).GetNormalized();
		
		
		if (Input::GetKeyDown(KeyCode::Q)) m_position += 0.1f * m_up;
		if (Input::GetKeyDown(KeyCode::E)) m_position -= 0.1f * m_up;
		
		
		if (Input::GetKeyDown(KeyCode::Up)) m_forward = Rotate(m_forward, -1, Cross(m_forward, m_up).GetNormalized());
		if (Input::GetKeyDown(KeyCode::Down)) m_forward = Rotate(m_forward, 1, Cross(m_forward, m_up).GetNormalized());



		if (Input::GetKeyDown(KeyCode::Left)) m_forward = Rotate(m_forward, 1, m_up);
		if (Input::GetKeyDown(KeyCode::Right)) m_forward = Rotate(m_forward, -1, m_up);
		

		RecalculateVewMatrix();
	}

	void Camera::OnEvent(Event & event)
	{
		if (event.type == Event::MouseMoved && Input::GetMouseButtonDown(MouseCode::ButtonRight))
		{
		}
	}
	/**Camera::Camera(f32 fovy, f32 aspect, f32 zNear, f32 zFar) :
		m_fov(fovy),
		m_aspectRatio(aspect),
		m_zNear(zNear),
		m_zFar(zFar),
		m_projectionMatrix(Perspective(fovy* MATH_RADIANS, aspect, zNear, zFar))
	{
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
	void Camera::UpdateView()
	{
		m_position = CalculatePosition();
		m_viewMatrix = Inverse(TranslateMatrix4(Matrix4f::Identity, m_position) * toMatrix4(GetOrientation()));
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
	void Camera::UpdateProjection()
	{
		m_aspectRatio = (f32)m_viewPortSize.x / (f32)m_viewPortSize.y;
		m_projectionMatrix = Perspective(m_fov * MATH_RADIANS, m_aspectRatio, m_zNear, m_zFar);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	Vector2f Camera::PanSpeed() const
	{
		f32 x = min(m_viewPortSize.x / 1000, 2.4f); // max = 2.4f
		f32 xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		f32 y = min(m_viewPortSize.y / 1000.0f, 2.4f); // max = 2.4f
		f32 yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}
	void Camera::OnUpdate(f32 ftime)
	{

		if (Input::GetKeyDown(KeyCode::LAlt))
		{
			const Vector2f& mouse{ Input::GetMousePosition(Application::GetInstance().GetWindow()).x, 
								   Input::GetMousePosition(Application::GetInstance().GetWindow()).y };
			Vector2f delta = (mouse - m_initialMousePosition) * 0.003f;
			m_initialMousePosition = mouse;
			if (Input::GetMouseButtonDown(MouseCode::ButtonMiddle))
				MousePan(delta);
			else if (Input::GetMouseButtonDown(MouseCode::ButtonLeft))
				MouseRotate(delta);
			else if (Input::GetMouseButtonDown(MouseCode::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}
	void Camera::OnEvent(Event & event)
	{
		if (event.type == Event::MouseWheelScrolled) {
			float delta = event.mouseWheelScroll.delta;
			MouseZoom(16);
			UpdateView();
		}
	}


	float Camera::ZoomSpeed() const
	{
		float distance = m_distance * 0.2f;
		distance = max(distance, 0.0f);
		float speed = distance * distance;
		speed = max(speed, 100.0f); // max speed = 100
		return speed;
	}
	void Camera::MousePan(const Vector2f & delta)
	{
		Vector2f vSpd = PanSpeed();
		m_focalPoint += -GetRightDirection() * delta.x * vSpd.x * m_distance;
		m_focalPoint += GetUpDirection() * delta.y * vSpd.y * m_distance;
	}

	void Camera::MouseRotate(const Vector2f & delta)
	{
		float yawSign = GetUpDirection().y < 0 ? 1.0f : 1.0f;
		m_yaw += yawSign * delta.x * RotationSpeed();
		m_pitch += delta.y * RotationSpeed(); UpdateView();
	}

	void Camera::MouseZoom(f32 delta)
	{
		m_distance -= delta * ZoomSpeed();

		if (m_distance < 1.0f)
		{
			m_focalPoint += GetForwardDirection();
			m_distance = 1.0f;
		}
	}

	Vector3f Camera::GetUpDirection() const
	{
		return Rotate(GetOrientation(), Vector3f(0.0f, 1.0f, 0.0f));
	}

	Vector3f Camera::GetRightDirection() const
	{
		return Rotate(GetOrientation(), Vector3f(1.0f, 0.0f, 0.0f));
	}

	Vector3f Camera::GetForwardDirection() const
	{
		return Rotate(GetOrientation(), Vector3f(0.0f, 0.0f, -1.0f));
	}

	Vector3f Camera::CalculatePosition() const
	{
		return m_focalPoint - GetForwardDirection() * m_distance;
	}

	Quaternion Camera::GetOrientation() const
	{
		return Quaternion(Vector3f(-m_pitch, -m_yaw, 0.0f));
	}*/
}