#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <Engine/Core/Config.h>
#include <Engine/Render/Texture.h>
#include <Engine/Render/CommandBuffer.h>
namespace MeteorEngine
{ 
	class FrameBuffer;
	enum SubPassContents
	{
		INLINE,
		SECONDARY
	};
	struct RenderPassDesc
	{
		Texture2D**		Attachments;
		TextureType*	AttachmentTypes;
		u32				AttachmentCount;
		bool			Clear = true;
		bool			SwapChainTarget = false;
	};
	class METEOR_API RenderPass
	{
	public:
		virtual ~RenderPass() {}
		static RenderPass* Create(const RenderPassDesc&);

		virtual void BeginRenderpass(CommandBuffer* commandBuffer, float* clearColour, FrameBuffer* frame, SubPassContents contents, const Vector2u&) const = 0;
		virtual void EndRenderpass(CommandBuffer* commandBuffer) = 0;


		virtual s32 GetAttachmentCount() const = 0;
	};
}
#endif

