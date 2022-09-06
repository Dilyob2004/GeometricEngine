#include <Engine/Render/CameraController2D.h>
#include <Engine/Core/Input.h>
namespace MeteorEngine
{
    CameraController2D::CameraController2D(float aspectRatio):
        m_aspectRatio(aspectRatio),
        m_camera(-aspectRatio * m_zoomLevel, aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
    {

    }
    CameraController2D::~CameraController2D()
    {

    }
    void CameraController2D::OnUpdate(float ftime)
    {
		if (Input::GetMouseButtonDown(MouseCode::ButtonMiddle))
		{
			Vector2f mouse{ Input::GetMousePosition().x, Input::GetMousePosition().y };

			Vector2f position = mouse * ftime * m_speed;
			m_position = Vector3f(position.x, position.y, 0);
		}
        if(Input::GetKeyDown(KeyCode::W)) m_position.y += ftime * m_speed;
        if(Input::GetKeyDown(KeyCode::S)) m_position.y -= ftime * m_speed;
        if(Input::GetKeyDown(KeyCode::D)) m_position.x += ftime * m_speed;
        if(Input::GetKeyDown(KeyCode::A)) m_position.x -= ftime * m_speed;
//
        m_camera.SetPosition(m_position);
        m_camera.SetRotation(0);

        m_speed = m_zoomLevel;
    }
    void CameraController2D::OnResize(const Vector2u& size)
    {
        m_aspectRatio = (float)size.x / (float)size.y;
        m_camera.SetProjectionMatrix(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    }
    void CameraController2D::OnEvent(Event &event)
    {
        if(event.type == Event::MouseWheelScrolled)
        {
            m_zoomLevel -= event.mouseWheelScroll.delta / 2.f;
            m_zoomLevel = max(m_zoomLevel, 0.3f);
            m_camera.SetProjectionMatrix(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

        }
		if (event.type == Event::MouseButtonPressed)
		{
		}

        /*if(event.type == Event::Resized)
        {
            OnResize({event.size.width, event.size.height});
        }*/

    }
}
