#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include "../Core/Config.h"
#include "../Math/Vector4.h"
#include "Texture.h"
#include "Camera2D.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
namespace MeteorEngine
{
    class METEOR_API Renderer
    {
    public:
        virtual ~Renderer(){}
        virtual void InitEngine() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) = 0;
        virtual void SetupProjection2D(Camera2D) = 0;
		virtual void SetupProjection3D(Camera) = 0;
		virtual void DrawQuad(const Matrix4f&, const Vector4f&) = 0;

		virtual void DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color) = 0;
		virtual void DrawTextureQuad(const std::shared_ptr<Texture2D> &, const Vector3f &, const Vector3f&, const Vector2f& ) = 0;
        virtual void SetClearColor(const Vector4f&) = 0;
        virtual void SetViewPort(s32, s32, u32, u32) = 0;
        virtual void Clear() = 0;
    };
    class METEOR_API RendererCommand
    {
    public:
        static void InitEngine();
        static void DrawIndexed(const std::shared_ptr<VertexArray>&);

        static void SetupProjection2D(Camera2D);
		static void SetupProjection3D(Camera);
		static void DrawQuad(const Matrix4f&, const Vector4f&);
		static void DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color);
		static void DrawQuad2D(const Vector2f& position, const Vector2f& rotation, const Vector2f& scale, const Vector4f& color);
        static void DrawTextureQuad(const std::shared_ptr<Texture2D> &, const Vector3f &, const Vector3f&, const Vector2f& );
        static void SetClearColor(const Vector4f&);
        static void SetViewPort(s32, s32, u32, u32);
        static void Clear();
    private:
        static Renderer *renderer;
    };
}
#endif // RENDERER_H
