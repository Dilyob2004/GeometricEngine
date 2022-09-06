#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <Engine/Math/Matrix4.h>
#include <Engine/Core/Event.h>
namespace MeteorEngine
{
    class Camera2D
    {
    public:
        Camera2D():
            m_rotation(0)
		{
		}
        Camera2D(f32 left, f32 right, f32 bottom, f32 top);
        void SetProjectionMatrix(f32 left, f32 right, f32 bottom, f32 top);
        const Vector3f& GetPosition() const { return m_position; }
        void SetPosition(const Vector3f& position) { m_position = position; RecalculateVewMatrix(); }

        f32 GetRotation() const { return m_rotation; }
        void SetRotation(f32 rotation) { m_rotation = rotation;  RecalculateVewMatrix();}
        const Matrix4f & GetProjectionMatrix() const { return m_projectionMatrix; }
        const Matrix4f & GetViewMatrix() const { return m_viewMatrix; }
        const Matrix4f & GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
    private:
        void RecalculateVewMatrix();
    private:
        Matrix4f m_projectionMatrix;
        Matrix4f m_viewMatrix;
        Matrix4f m_viewProjectionMatrix;
        Vector3f m_position;
        f32 m_rotation;

    };
}
#endif // CAMERA2D_H
