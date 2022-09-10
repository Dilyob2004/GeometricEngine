#include <Engine/Render/CameraController2D.h>
#include <Engine/Core/Input.h>
namespace MeteorEngine
{
    CameraController2D::CameraController2D(float aspectRatio):
        m_aspectRatio(aspectRatio),
        m_camera(-1, 1, -1, 1)
    {

    }
    CameraController2D::~CameraController2D()
    {

    }
    void CameraController2D::OnResize(const Vector2u& size)
    {
        m_aspectRatio = (float)size.x / (float)size.y;
        m_camera.SetProjectionMatrix(-1, 1, -1, 1);
    }
    void CameraController2D::OnEvent(Event &event)
    {
        if(event.type == Event::Resized)
        {
        }

    }
}
