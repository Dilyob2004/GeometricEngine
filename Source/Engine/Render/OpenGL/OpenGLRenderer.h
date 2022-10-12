#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <Engine/Render/Renderer.h>
namespace MeteorEngine
{
    class METEOR_API OpenGLRenderer : public Renderer
    {
    public:
        virtual ~OpenGLRenderer(){}
        virtual void InitEngine() override;
		virtual void DrawQuad(const Matrix4f&, const Vector4f&)override;

		virtual void DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color) override;
        virtual void DrawTextureQuad(const std::shared_ptr<Texture> &, const Vector3f &, const Vector3f&, const Vector2f& )override;

        virtual void SetupProjection2D(Camera2D)override;
		virtual void SetupProjection3D(Camera)override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) override;
        virtual void SetClearColor(const Vector4f& ) override;
        virtual void SetViewPort(s32 x, s32 y, u32 w, u32 h) override;
        virtual void Clear() override;


    };
}
#endif // OPENGLRENDERER_H
