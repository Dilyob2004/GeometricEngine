#include <Engine/Render/Renderer.h>
#include <Engine/Render/OpenGL/OpenGLRenderer.h>
namespace MeteorEngine
{
    Renderer *RendererCommand::renderer = new OpenGLRenderer;
    void RendererCommand::InitEngine()
    {
        renderer->InitEngine();
    }
    void RendererCommand::SetCamera(Camera2D camera)
    {
        renderer->SetCamera(camera);
    }
	void RendererCommand::SetCamera(Camera camera)
	{
		renderer->SetCamera(camera);
	}
    void RendererCommand::DrawQuad(const Matrix4f& transform, const Vector4f& color)
    {
        renderer->DrawQuad(transform, color);
    }    

	void RendererCommand::DrawQuad(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale, const Vector4f& color, bool connectCamera)
	{
		renderer->DrawQuad(position, rotation, scale, color, connectCamera);
    }
    void RendererCommand::DrawTextureQuad(const std::shared_ptr<Texture2D> &texture, const Vector3f &position, const Vector2f& size)
    {
        renderer->DrawTextureQuad(texture, position, size);

    }

    void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        renderer->DrawIndexed(vertexArray);
    }
    void RendererCommand::SetClearColor(const Vector4f& v)
    {
        renderer->SetClearColor(v);
    }
    void RendererCommand::Clear()
    {
        renderer->Clear();
    }
    void RendererCommand::SetViewPort(s32 x, s32 y, u32 w, u32 h)
    {
        renderer->SetViewPort(x, y, w, h);
    }
}
