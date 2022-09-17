
#include <Engine/Render/Camera2D.h>
#include <Engine/Math/MathUtils.h>

namespace MeteorEngine
{
    Camera2D::Camera2D(f32 left, f32 right, f32 bottom, f32 top):
        m_projectionMatrix(Ortho(left, right, bottom, top)), m_viewMatrix(1)
    {
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
    void Camera2D::SetProjectionMatrix(f32 left, f32 right, f32 bottom, f32 top)
    {
        m_projectionMatrix = Ortho(left, right, bottom, top);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
    void Camera2D::RecalculateVewMatrix()
    {
        Matrix4f transformC = Translate(Matrix4f::Identity, m_position) *
                                Rotate(Matrix4f::Identity, m_rotation, Vector3f(0, 0, 1));


        m_viewMatrix = Inverse(transformC);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
