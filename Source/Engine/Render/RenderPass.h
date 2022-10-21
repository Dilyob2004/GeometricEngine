#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <Engine/Core/Config.h>
#include <Engine/Render/Texture.h>
namespace MeteorEngine
{ 
	struct RenderPassDesc
	{
		Texture**		Attachments;
		TextureType*	AttachmentTypes;
		u32				AttachmentCount;
		bool			Clear = true;
		bool			ClearSwapChainTarget = false;
	};
	class METEOR_API RenderPass
	{
	public:
		virtual ~RenderPass() {}
		static RenderPass* Create(const RenderPassDesc&);

	};
}
#endif

