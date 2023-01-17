#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include <Engine/Math/Matrix4.h>
#include <Engine/Render/Texture.h>
#include <Engine/Render/Camera.h>
#include <Engine/Render/Camera2D.h>
#include <Engine/Render/SwapChain.h>
#include <Engine/Render/Pipeline.h>
namespace MeteorEngine
{
	class METEOR_API Renderer
	{
	public:
		virtual ~Renderer() {}

		virtual void Init(RenderContext*, const Vector2u& size, bool vsync) = 0;
		virtual void Begin() = 0;
		virtual void Present() = 0;
		virtual void Resize(const Vector2u& size) = 0;
		virtual void ClearSwapChainImages() const = 0;
		virtual SwapChain* GetMainSwapChain() const = 0;


		void SetupProjection2D(Camera2D) {}
		void SetupProjection3D(Camera) {}
		void DrawQuad(const Matrix4f&, const Vector4f&) {}
		void DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color) {}
		void DrawTextureQuad(const std::shared_ptr<Texture>&, const Vector3f&, const Vector3f&, const Vector2f&) {}
		void SetClearColor(const Vector4f&) {}
		void SetViewPort(s32, s32, u32, u32) {}
		void Clear() {}
    };
    class METEOR_API RendererCommand
    {
    public:
        static void SetupProjection2D(Camera2D){}
		static void SetupProjection3D(Camera){}
		static void DrawQuad(const Matrix4f&, const Vector4f&){}
		static void DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color){}
		static void DrawQuad2D(const Vector2f& position, const Vector2f& rotation, const Vector2f& scale, const Vector4f& color){}
        static void DrawTextureQuad(const std::shared_ptr<Texture> &, const Vector3f &, const Vector3f&, const Vector2f& ){}
        static void SetClearColor(const Vector4f&){}
        static void SetViewPort(s32, s32, u32, u32){}
		static void Clear() {}

	private:
		static Renderer* m_Renderer;
    };
}
#endif // RENDERER_H
