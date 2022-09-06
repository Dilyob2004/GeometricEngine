#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Engine/Render/Camera2D.h>
#include <Engine/Math/Vector2.h>
namespace MeteorEngine
{
    class CameraController2D
    {
    public:
        CameraController2D(float);
        ~CameraController2D();
        void OnUpdate(float ftime);
        void OnEvent(Event &);
        void OnResize(const Vector2u& size);
        Camera2D &GetCamera() { return m_camera; }
        const Camera2D &GetCamera() const { return m_camera; }
    private:
        f32         m_zoomLevel = 1, m_aspectRatio = 1, m_speed = 1;
        Camera2D    m_camera;
        Vector3f    m_position = {0, 0, 0};
    };
}

#endif // CAMERACONTROLLER_H
