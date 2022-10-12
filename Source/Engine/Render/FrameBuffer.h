#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Config.h>
#include <Engine/Render/Texture.h>
#include <vector>
namespace MeteorEngine
{
	struct FrameBufferTextureSpec
	{
		FrameBufferTextureSpec() = default;
		FrameBufferTextureSpec(Texture* texure) :
			m_Texture(texure)
		{
		}
		Texture *m_Texture;
	};
	struct FrameBufferAttachmentSpec
	{
		FrameBufferAttachmentSpec() = default;
		FrameBufferAttachmentSpec(std::initializer_list<FrameBufferTextureSpec> attachments):
			Attachments(attachments)
		{
		}
		std::vector<FrameBufferTextureSpec> Attachments;
	};
    struct FrameBufferSpec
    {
		FrameBufferSpec()		= default;
		FrameBufferAttachmentSpec   Attachments;
        Vector2u					Size;
        u32							Samples = 2;
    };
    class METEOR_API FrameBuffer
    {
    public: 
        virtual ~FrameBuffer() {}
        virtual void Bind()     const = 0;
        virtual void UnBind()   const = 0;
        virtual void Resize(const Vector2u &) = 0;
        virtual u32 GetFrameBuffer() const  = 0;
        virtual const FrameBufferSpec& GetSpecification() const = 0;
        static FrameBuffer* Create(const FrameBufferSpec&);
    };
}
#endif // FRAMEBUFFER_H
