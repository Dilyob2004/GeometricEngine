#include "Renderer2D.h"
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>
#include <Engine/Math/Quaternion.h>

struct
{
	FMatrix4 ViewProjection { 1.0f };
	FMatrix4 Transform { 1.0f };
}CVSBuffer;

struct
{
	Vector4f Color {1.0f, 1.0f, 1.0f, 1.0f};
}CPSBuffer;

RHIPipelineState* Renderer2D::PipelineState = NULL;
RHIVertexBuffer* Renderer2D::VertexBuffer = NULL;
RHIIndexBuffer* Renderer2D::IndexBuffer = NULL;
RHIUniformBuffer* Renderer2D::UniformBufferVS = NULL;
RHIUniformBuffer* Renderer2D::UniformBufferPS = NULL;
RHISamplerState* Renderer2D::SamplerBilinearWrap = NULL;

void Renderer2D::Init()
{


	TArray<BufferElement> ShaderElements;
	ShaderElements.Push(BufferElement("POSITION", ShaderElementType::Float3));
	ShaderElements.Push(BufferElement("TEXCOORD", ShaderElementType::Float2));

	RHIPipelineStateDefinition Define;
	Define.BlendStateDefinition = RHIBlendStateDefinition();
	Define.DepthStencilStateDefinition = RHIDepthStencilStateDefinition();
	Define.RasterizerStateDefinition = RHIRasterizerStateDefinition();
	Define.PixelShader = GPixelShaderMap[("ScreenPixelShader")];
	Define.VertexShader = GVertexShaderMap[("ScreenVertexShader")];
	Define.VertexParameters = ShaderElements;
	PipelineState = GDynamicRHI->RHICreatePipelineState(Define);


	F32 VerticesData[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f
	};
	U32 IndicesData[] = { 0, 2, 1, 0, 3, 2 };
		
	VertexBuffer = GDynamicRHI->RHICreateVertexBuffer(VerticesData, sizeof(VerticesData), 20);
	IndexBuffer = GDynamicRHI->RHICreateIndexBuffer(IndicesData, 24);

	UniformBufferVS = GDynamicRHI->RHICreateUniformBuffer(&CVSBuffer, sizeof(CVSBuffer), RHIUsage::Default);
	UniformBufferPS = GDynamicRHI->RHICreateUniformBuffer(&CPSBuffer, sizeof(CPSBuffer), RHIUsage::Default);
	
	SamplerBilinearWrap = GDynamicRHI->RHICreateSamplerState(RHISamplerStateDefinition());

}

void Renderer2D::BeginFrame(const Camera& SceneCamera)
{
	GDynamicRHI->RHISetPipelineState(PipelineState);
	CVSBuffer.ViewProjection = SceneCamera.GetViewProjection();
}

void Renderer2D::DrawSprite(FSprite* Sprite, const Vector4f& Color, const Vector2f& Position, F32 Rotation, const Vector2f& Scale)
{
	CVSBuffer.Transform = MathUtils::Translate(FMatrix4::Identity, 
		Vector3f(Position.x, Position.y, 0.0f)) * 
		MathUtils::QuaternionToMatrix4(FQuaternion(Vector3f(0.0f, 0.0f, Rotation * MATH_PI / 180))) * MathUtils::Scale(FMatrix4::Identity, Vector3f(Scale.x, Scale.y, 0.0f));
	CPSBuffer.Color = Color;

	GDynamicRHI->RHIUpdateUniformBuffer(UniformBufferVS, &CVSBuffer, sizeof(CVSBuffer));
	GDynamicRHI->RHISetVertexShaderUniformBuffer(UniformBufferVS);


	GDynamicRHI->RHIUpdateUniformBuffer(UniformBufferPS, &CPSBuffer, sizeof(CPSBuffer));
	GDynamicRHI->RHISetPixelShaderUniformBuffer(UniformBufferPS);


	GDynamicRHI->RHISetPixelShaderTexture(Sprite->GetTextureRHI());
	GDynamicRHI->RHISetPixelShaderSampler(SamplerBilinearWrap);


}
void Renderer2D::EndFrame()
{
	GDynamicRHI->RHIDrawPrimitiveIndexed(VertexBuffer, IndexBuffer, 6, 0);
}

