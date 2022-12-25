#ifndef PIPELINE_H
#define PIPELINE_H

#include <Engine/Render/Shader.h>
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{

	struct PipelineInfo
	{
		CullMode cullMode = CullMode::BACK;
		PolygonMode polygonMode = PolygonMode::FILL;
		BlendMode blendMode = BlendMode::None;
		DrawType drawType = DrawType::TRIANGLE;

		Shader* PipelineShader;
		bool TransparencyEnabled = false;
		bool SwapChainTarget = false;
		bool DepthBiasEnabled = false;
		bool ClearTargets = false;

		Texture* ColorTargets[10];
		Texture* DepthTarget = NULL;
		float clearColor[4] = {0, 0, 0, 0};
		float DepthBiasConstantFactor = 0.0f;
		float DepthBiasSlopeFactor = 0.0f;
	};

	class METEOR_API Pipeline
	{
	public:
		static Pipeline* Create(const PipelineInfo&);
		virtual void Begin(CommandBuffer*) = 0;
		virtual void End(CommandBuffer*)= 0;

		virtual void ClearRenderTargets(CommandBuffer* commandBuffer) = 0;
		virtual Shader* GetShader() = 0;
	};
}
#endif // !PIPELINE_H
