#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Engine/Render/Camera2D.h>
#include <Engine/Math/Vector2.h>
namespace MeteorEngine
{
    class CameraController2D
    {
    public:
        CameraController2D(f32);
        ~CameraController2D();
        void OnEvent(Event &);
        void OnResize(const Vector2u& size);
        Camera2D &GetCamera() { return m_camera; }
        const Camera2D &GetCamera() const { return m_camera; }
    private:
        f32          m_aspectRatio = 1;
        Camera2D    m_camera;
    };
}

#endif // CAMERACONTROLLER_H
