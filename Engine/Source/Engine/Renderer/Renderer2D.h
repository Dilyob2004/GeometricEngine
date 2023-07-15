#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <Engine/Core/Config.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Renderer/Camera.h>
#include <Engine/Math/Vector2.h>
#include <Engine/RendererCore/Sprite.h>

class Renderer2D
{
public:
	static void Init();
	static void BeginFrame(const Camera& SceneCamera);
	static void DrawSprite(FSprite*, const Vector4f& Color, const Vector2f& Position, F32 rotation, const Vector2f& Scale);
	static void EndFrame();


private:
	static RHIPipelineState* PipelineState;
	static RHIVertexBuffer* VertexBuffer;
	static RHIIndexBuffer* IndexBuffer;
	static RHIUniformBuffer* UniformBufferVS;
	static RHIUniformBuffer* UniformBufferPS;
	static RHISamplerState* SamplerBilinearWrap;
};

#endif // !RENDERER2D_H
