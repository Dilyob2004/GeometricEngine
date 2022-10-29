#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <Engine/Core/Config.h>
#include <Engine/Render/RenderPass.h>
#include <vector>
namespace MeteorEngine
{
    struct FrameBufferDesc
    {
		Texture**		Attachments;
		TextureType*	AttachmentTypes;
		RenderPass*		RenderPass;
		Vector2u		Size;
		u32				AttachmentCount;
		u32				MSAALevel = 1;
		bool			ScreenFBO = false;
		u32				Layer = 0;
    };
    class METEOR_API FrameBuffer
    {
    public:
		static FrameBuffer* Create(const FrameBufferDesc&);
        virtual ~FrameBuffer() {}

		virtual u32 GetAttachmentCount() const = 0;
        virtual const FrameBufferDesc& GetSpecification() const = 0;
    };
}
#endif // FRAMEBUFFER_H
